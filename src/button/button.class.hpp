#ifndef BUTTON_CLASS_HPP
#define BUTTON_CLASS_HPP
#include <Arduino.h>

class Button {
public:
  Button(uint8_t pin);
  void set();
  void unset();
  bool isTriggered();
private:
  static bool _isTriggered;
  static void trigger();
  bool isSet = false;
  uint8_t pin;
};


#endif