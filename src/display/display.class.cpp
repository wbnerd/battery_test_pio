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

void Display::startScreen(const __FlashStringHelper * text) {
  oled.clear();       // очистка
  oled.home();        // курсор в 0,0
  oled.setScale(1);   // масштаб текста (1..4
  oled.print(text);
  messageRow++;
}

void Display::appentScreenMessage(const __FlashStringHelper * text) {
  oled.setCursor(0, messageRow);   // масштаб текста (1..4
  oled.print(text);
  messageRow++;
}

void Display::clearScreen() {
  oled.clear();       // очистка
  oled.home();        // курсор в 0,0
  messageRow = 0;
}