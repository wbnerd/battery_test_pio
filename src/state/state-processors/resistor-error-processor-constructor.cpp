#include <blink/blink.class.hpp>
#include "state-processors.hpp"
#include <constants.hpp>

void resistorErrorEnter(StateProcessor* processor, StateStep from) {
  Serial.println();
  Serial.println("Resistor error initiated");

  blinker.appendBlinkTask(processor->thisStateBlinkTask);
}

void resistorErrorExit(StateProcessor* processor) {
  Serial.println("Resistor error exit");
}

StateProcessor* ResistorErrorStateProcessor() {
  StateProcessor* processor = new StateProcessor{
    RESISTOR_ERROR,
    {RESISTOR_ERROR, BLINK_LENGTH, BLINK_DELAY, true, 1000},
    resistorErrorEnter,
    resistorErrorExit
  };

  return processor;
}
