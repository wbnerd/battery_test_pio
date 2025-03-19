#include <blink/blink.class.hpp>
#include "state-processors.hpp"
#include <constants.hpp>
#include "di/di.hpp"
#include "display/display.class.hpp"

StateStep oledSetupIterate(StateProcessor* processor) {
  Container<Display>::set(new Display());

  return StateStep::INA_SETUP;
}

StateProcessor* OledSetupStateProcessor() {
  StateProcessor* processor = new StateProcessor{
    StateStep::OLED_SETUP,
    {StateStep::OLED_SETUP, BLINK_LENGTH, BLINK_DELAY, true, 1000},
    nullptr,
    nullptr,
    oledSetupIterate
  };

  return processor;
}