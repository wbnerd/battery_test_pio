#include "display.class.hpp"
#include "constants.hpp"
#include <GyverOLED.h>
#include <Arduino.h>

GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;

#define PARAMETER_SCREEN_ROW_LENGTH 128
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
  const char (*newParameterNames)[5]
) {
  clearScreen();

  parameterScreenTitle = title;
  parameterScreenLength = length;
  parameterScreenNames = newParameterNames;

  printParameterScreen(nullptr, true);
}

void Display::printParameterScreen(float * parameters, bool isNull) {
  clearScreen();
  oled.setCursor(0, 0);
  oled.print(parameterScreenTitle);

  // Print parameter names in two columns
  for (int i = 0; i < parameterScreenLength; i++) {
    int row = (i / 2) + 1;
    int col = (i % 2) * 64;

    oled.setCursor(col, row);
    oled.print(parameterScreenNames[i]);
    oled.print(":");

    oled.setCursor(col + PARAMETER_SCREEN_ROW_LENGTH / 4, row);

    if (isNull) {
      oled.print("0.00");
    } else {
      char result[5];
      floatToChars(parameters[i], result);
      oled.print(result);
    }
  }
}

void Display::updateParameterScreen(float * parameters) {
  printParameterScreen(parameters, false);
}

void Display::floatToChars(float value, char result[5]) {
  if (value == 0) {
    result[0] = '0';
    result[1] = '.';
    result[2] = '0';
    result[3] = '0';
    result[4] = '\0';
    return;
  }

  if (value >= 1000000000) {
    result[0] = '>';
    result[1] = '1';
    result[2] = 'M';
    result[3] = 'M';
    result[4] = '\0';
    return;
  }

  if (value < 0.001) {
    result[0] = '<';
    result[1] = '1';
    result[2] = 'u';
    result[3] = 'u';
    result[4] = '\0';
    return;
  }


  int intValue = (int)value;
  int d1, d2, d3;

  // 100 000 000
  if (value >= 100000000) {
    d1 = intValue / 100000000;
    d2 = (intValue / 10000000) % 10;
    d3 = (intValue / 1000000) % 10;

    result[0] = d1 + '0';
    result[1] = d2 + '0';
    result[2] = d3 + '0';
    result[3] = 'M';
    result[4] = '\0';
    return;
  }

  // 10 000 000
  if (value >= 10000000) {
    d1 = intValue / 10000000;
    d2 = (intValue / 1000000) % 10;
    d3 = (intValue / 100000) % 10;

    result[0] = d1 + '0';
    result[1] = d2 + '0';
    result[2] = 'M';
    result[3] = d3 + '0';
    result[4] = '\0';
    return;
  }

  // 1 000 000
  if (value >= 1000000) {
    d1 = intValue / 1000000;
    d2 = (intValue / 100000) % 10;
    d3 = (intValue / 10000) % 10;

    result[0] = d1 + '0';
    result[1] = 'M';
    result[2] = d2 + '0';
    result[3] = d3 + '0';
    result[4] = '\0';
    return;
  }

  // 100 000
  if (value >= 100000) {
    d1 = intValue / 100000;
    d2 = (intValue / 10000) % 10;
    d3 = (intValue / 1000) % 10;

    result[0] = d1 + '0';
    result[1] = d2 + '0';
    result[2] = d3 + '0';
    result[3] = 'k';
    result[4] = '\0';
    return;
  }

  // 10 000
  if (value >= 10000) {
    d1 = intValue / 10000;
    d2 = (intValue / 1000) % 10;
    d3 = (intValue / 100) % 10;

    result[0] = d1 + '0';
    result[1] = d2 + '0';
    result[2] = 'k';
    result[3] = d3 + '0';
    result[4] = '\0';
    return;
  }

  // 1 000
  if (value >= 1000) {
    d1 = intValue / 1000;
    d2 = (intValue / 100) % 10;
    d3 = (intValue / 10) % 10;

    result[0] = d1 + '0';
    result[1] = 'k';
    result[2] = d2 + '0';
    result[3] = d3 + '0';
    result[4] = '\0';
    return;
  }

  // 100
  if (value >= 100) {
    d1 = intValue / 100;
    d2 = (intValue / 10) % 10;
    d3 = intValue % 10;

    result[0] = d1 + '0';
    result[1] = d2 + '0';
    result[2] = d3 + '0';
    result[3] = ' ';
    result[4] = '\0';
    return;
  }

  // 10
  if (value >= 10) {
    d1 = intValue / 10;
    d2 = intValue % 10;
    d3 = (int)(value * 10) % 10;

    result[0] = d1 + '0';
    result[1] = d2 + '0';
    result[2] = '.';
    result[3] = d3 + '0';
    result[4] = '\0';
    return;
  }

  // 1
  if (value >= 1) {
    d1 = intValue / 1;
    d2 = (int)(value * 10) % 10;
    d3 = (int)(value * 100) % 10;

    result[0] = d1 + '0';
    result[1] = '.';
    result[2] = d2 + '0';
    result[3] = d3 + '0';
    result[4] = '\0';
    return;
  }

  // < 1m
  if (value < 0.001) {
    d1 = (int)(value * 1000) % 10;
    d2 = (int)(value * 10000) % 10;
    d3 = (int)(value * 100000) % 10;

    result[0] = 'u';
    result[1] = d1 + '0';
    result[2] = d2 + '0';
    result[3] = d3 + '0';
    result[4] = '\0';
    return;
  }

  // < 1
  if (value < 1) {
    d1 = (int)(value * 10) % 10;
    d2 = (int)(value * 100) % 10;
    d3 = (int)(value * 1000) % 10;

    result[0] = '.';
    result[1] = d1 + '0';
    result[2] = d2 + '0';
    result[3] = d3 + '0';
    result[4] = '\0';
    return;
  }
}
