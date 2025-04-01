#include "display.class.hpp"
#include "constants.hpp"
#include <GyverOLED.h>
#include <Arduino.h>

GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;

#define PARAMETER_SCREEN_ROW_LENGTH 20
#define PARAMETER_NAME_TAB 5

Display::Display() {
  oled.init(SDA_PIN, SCL_PIN);
  oled.clear();       // очистка
  oled.home();        // курсор в 0,0
  oled.setScale(1);   // масштаб текста (1..4)
}

void Display::startScreen(const __FlashStringHelper * text) {
  oled.clear();       // очистка
  oled.home();        // курсор в 0,0
  oled.setScale(1);   // масштаб текста (1..4
  oled.print(text);
  messageRow++;
}

void Display::appendScreenMessage(const __FlashStringHelper * text) {
  oled.setCursor(0, messageRow);
  oled.print(text);
  messageRow++;
}

void Display::clearScreen() {
  oled.clear();       // очистка
  oled.home();        // курсор в 0,0
  messageRow = 0;
}

void Display::setupParameterScreen(
  const __FlashStringHelper * title,
  int length,
  char parameterScreenNames[][5]
) {
  clearScreen();

  parameterScreenTitle = title;
  parameterScreenLength = length;
  parameterScreenNames = parameterScreenNames;

  printParameterScreen(nullptr, true);
}

void Display::printParameterScreen(long * parameters, bool isNull) {
  clearScreen();
  oled.setCursor(0, 0);
  oled.print(parameterScreenTitle);

  // Print parameter names in two columns
  for (int i = 0; i < parameterScreenLength; i++) {
    int row = (i / 2) + 1;  // Start from row 1 (after title)
    int col = (i % 2) * PARAMETER_SCREEN_ROW_LENGTH; // First column at 0, second column at 64

    oled.setCursor(col, row);
    oled.print(parameterScreenNames[i]);
    oled.print(":");

    oled.setCursor(col + PARAMETER_NAME_TAB, row);

    if (isNull) {
      oled.print("0.00");
    } else {
      oled.print(parameters[i]);
    }
  }
}

void Display::updateParameterScreen(long * parameters) {
  printParameterScreen(parameters, false);
}

void Display::floatToChars(float value, char result[4]) {
  // Handle zero case
  if (value == 0) {
    result[0] = '0';
    result[1] = '.';
    result[2] = '0';
    result[3] = '0';
    return;
  }

  // Handle negative numbers
  bool isNegative = value < 0;
  if (isNegative) {
    value = -value;
  }

  // Get the magnitude of the number
  int magnitude = 0;
  while (value >= 10) {
    value /= 10;
    magnitude++;
  }
  while (value < 1 && value != 0) {
    value *= 10;
    magnitude--;
  }

  // Round to 2 decimal places
  value = round(value * 100.0) / 100.0;

  // Convert to string with 2 decimal places
  char temp[8];
  dtostrf(value, 0, 2, temp);

  // Copy the first 4 characters to result
  for (int i = 0; i < 4; i++) {
    result[i] = temp[i];
  }

  // If the number was negative, shift right and add minus sign
  if (isNegative) {
    for (int i = 2; i >= 0; i--) {
      result[i + 1] = result[i];
    }
    result[0] = '-';
  }
}
