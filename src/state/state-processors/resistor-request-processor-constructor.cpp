#include <blink/blink.class.hpp>
#include "state-processors.hpp"
#include <constants.hpp>

void resistorRequestEnter(StateProcessor* processor, StateStep from) {
  Serial.println("Entering Resistor Request State");

  blinker.appendBlinkTask(processor->blinkTask);
}

void resistorRequestExit(StateProcessor* processor) {
  Serial.println("Resistor request exit");
}

StateProcessor* ResistorRequestStateProcessor() {
  StateProcessor* processor = new StateProcessor{
    RESISTOR_REQUEST,
    {RESISTOR_REQUEST, BLINK_LENGTH, BLINK_DELAY, true, 1000},
    resistorRequestEnter,
    resistorRequestExit
  };

  return processor;
}