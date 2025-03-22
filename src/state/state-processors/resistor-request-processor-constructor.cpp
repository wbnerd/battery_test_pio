#include <blink/blink.class.hpp>
#include "state-processors.hpp"
#include <constants.hpp>

StateStep resistorRequestEnter(StateProcessor* processor) {
  return StateStep::RESISTOR_REQUEST;
}

StateProcessor* ResistorRequestStateProcessor() {
  StateProcessor* processor = new StateProcessor{
    RESISTOR_REQUEST,
    {RESISTOR_REQUEST, BLINK_LENGTH, BLINK_DELAY, true, 1000},
    resistorRequestEnter,
    nullptr,
    nullptr,
  };

  return processor;
}