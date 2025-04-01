#ifndef DISPLAY_CLASS_HPP
#define DISPLAY_CLASS_HPP

#include <GyverOLED.h>

class Display {
  private:
    uint8_t messageRow = 0;
    const __FlashStringHelper * parameterScreenTitle = nullptr;
    int parameterScreenLength = 0;
    char parameterScreenNames[][5];

    void printParameterScreen(long * parameters, bool isNull);
    void floatToChars(float value, char result[5]);

  public:
    Display();
    void startScreen(const __FlashStringHelper * text);
    void appendScreenMessage(const __FlashStringHelper * text);
    void clearScreen();

    void setupParameterScreen(const __FlashStringHelper * title, int parametersLength, char parametersNames[][5]);
    void updateParameterScreen(long * parameters);

};

#endif