#include "state-processors.hpp"
#include <constants.hpp>

StateStep resistorErrorEnter(StateProcessor* processor) {
  return StateStep::RESISTOR_ERROR;
}

StateProcessor* ResistorErrorStateProcessor() {
  StateProcessor* processor = new StateProcessor{
    RESISTOR_ERROR,
    {RESISTOR_ERROR, BLINK_LENGTH, BLINK_DELAY, true, 1000},
    resistorErrorEnter,
    nullptr,
    nullptr
  };

  return processor;
}
