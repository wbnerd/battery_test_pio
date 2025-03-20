#ifndef DISPLAY_CLASS_HPP
#define DISPLAY_CLASS_HPP

#include <GyverOLED.h>

GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;

class Display {
  private:
    uint8_t errorRow = 0;

  public:
    void startErrorMessage(const __FlashStringHelper * text);
    void appendErrorMessage(const __FlashStringHelper * text);
    void clearErrorMessage();
};

#endif