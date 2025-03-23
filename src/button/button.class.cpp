#include "button.class.hpp"
#include "Arduino.h"
#include "constants.hpp"

bool Button::_isTriggered = false;

void IRAM_ATTR Button::trigger() {
  _isTriggered = true;
}

Button::Button() {
}

void Button::set() {
  if (isSet) {
    return;
  }

  attachInterrupt(BUTTON_PIN, Button::trigger, FALLING);

  isSet = true;
  _isTriggered = false;
}

void Button::unset() {
  detachInterrupt(BUTTON_PIN);

  isSet = false;
  _isTriggered = false;
}

bool Button::isTriggered() {
  return _isTriggered;
}
