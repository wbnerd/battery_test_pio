#include "button.class.hpp"
#include "Arduino.h"

bool Button::_isTriggered = false;

void IRAM_ATTR Button::trigger() {
  _isTriggered = true;
}

Button::Button(uint8_t pin) : pin(pin) {
  pinMode(pin, INPUT_PULLUP);
}

void Button::set() {
  if (isSet) {
    return;
  }

  attachInterrupt(pin, Button::trigger, FALLING);

  isSet = true;
  _isTriggered = false;
}

void Button::unset() {
  detachInterrupt(pin);

  isSet = false;
  _isTriggered = false;
}

bool Button::isTriggered() {
  return _isTriggered;
}
