#include <blink/blink.class.hpp>
#include "state-processors.hpp"
#include <constants.hpp>

StateStep resistorCheckEnter(StateProcessor* processor) {
  return StateStep::RESISTOR_CHECK;
}

StateProcessor* ResistorCheckStateProcessor() {
  StateProcessor* processor = new StateProcessor{
    RESISTOR_CHECK,
    {RESISTOR_CHECK, BLINK_LENGTH, BLINK_DELAY, true, 1000},
    resistorCheckEnter,
    nullptr,
    nullptr,
  };

  return processor;
}