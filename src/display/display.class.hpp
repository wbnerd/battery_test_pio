#ifndef DISPLAY_CLASS_HPP
#define DISPLAY_CLASS_HPP

#include <GyverOLED.h>

class Display {
  private:
    uint8_t messageRow = 0;

  public:
    Display();
    void startScreen(const __FlashStringHelper * text);
    void appendScreenMessage(const __FlashStringHelper * text);
    void clearScreen();
};

#endif