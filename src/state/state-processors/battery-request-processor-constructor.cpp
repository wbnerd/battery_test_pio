#include <blink/blink.class.hpp>
#include "state-processors.hpp"
#include <constants.hpp>
#include "di/di.hpp"
#include "button/button.class.hpp"
#include "display/display.class.hpp"

StateStep batteryRequestEnter(StateProcessor* processor) {
  auto button = Container<Button>::get();
  button->set();

  auto display = Container<Display>::get();

  display->startScreen(F("Bat is now not installed"));
  display->appentScreenMessage(F("too low or unknown"));
  display->appentScreenMessage(F("install good battery"));
  display->appentScreenMessage(F("and press button"));

  return StateStep::BATTERY_REQUEST;
}

StateStep batteryRequestExit(StateProcessor* processor) {
  auto button = Container<Button>::get();

  button->unset();

  auto display = Container<Display>::get();

  display->clearScreen();

  return StateStep::BATTERY_REQUEST;
}

StateStep batteryRequestIterate(StateProcessor* processor) {
  auto button = Container<Button>::get();

  if (button->isTriggered())
  {
    return StateStep::BATTERY_CHECK;
  }

  return StateStep::BATTERY_REQUEST;
}


StateProcessor* BatteryRequestStateProcessor() {
  StateProcessor* processor = new StateProcessor{
    BATTERY_REQUEST,
    {BATTERY_REQUEST, BLINK_LENGTH, BLINK_DELAY, true, 1000},
    batteryRequestEnter,
    batteryRequestExit,
    batteryRequestIterate
  };

  return processor;
}