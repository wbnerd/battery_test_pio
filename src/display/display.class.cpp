#include "display.class.hpp"
#include "constants.hpp"
#include <GyverOLED.h>

GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;

Display::Display() {
  oled.init(SDA_PIN, SCL_PIN);
  oled.clear();       // очистка
  oled.home();        // курсор в 0,0
  oled.setScale(1);   // масштаб текста (1..4)
  oled.print("BatteryTest");
}

void Display::startErrorMessage(const __FlashStringHelper * text) {
  oled.clear();       // очистка
  oled.home();        // курсор в 0,0
  oled.setScale(1);   // масштаб текста (1..4
  oled.print(text);
  errorRow++;
}

void Display::appendErrorMessage(const __FlashStringHelper * text) {
  oled.setCursor(0, errorRow);   // масштаб текста (1..4
  oled.print(text);
  errorRow++;
}

void Display::clearErrorMessage() {
  oled.clear();       // очистка
  oled.home();        // курсор в 0,0
  errorRow = 0;
}