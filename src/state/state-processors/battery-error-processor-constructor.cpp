#include "state-processors.hpp"
#include <constants.hpp>
#include "di/di.hpp"
#include "display/display.class.hpp"

StateStep batteryErrorEnter(StateProcessor* processor) {
  auto display = Container<Display>::get();

  display->startScreen(F("Bat voltage is > 15V"));
  display->appentScreenMessage(F("Turn off and check"));

  return StateStep::BATTERY_ERROR;
}

StateProcessor* BatteryErrorStateProcessor() {
  StateProcessor* processor = new StateProcessor{
    BATTERY_ERROR,
    {BATTERY_ERROR, BLINK_LENGTH, BLINK_DELAY, true, 1000},
    batteryErrorEnter,
    nullptr,
    nullptr,
  };

  return processor;
}