#include "button.class.hpp"
#include "Arduino.h"
#include "constants.hpp"

static bool _isTriggered = false;

Button::Button() {

}

void Button::set() {
  if (isSet)
  {
    return;
  }

  attachInterrupt(BUTTON_PIN, [] {
    _isTriggered = true;
  }, FALLING);

  isSet = true;
}

void Button::unset() {
  detachInterrupt(BUTTON_PIN);

  isSet = false;
}

bool Button::isTriggered() {
  return _isTriggered;
}