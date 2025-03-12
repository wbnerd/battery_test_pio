#include <blink/blink.class.hpp>
#include "state-processors.hpp"
#include <constants.hpp>

void resistorCheckEnter(StateProcessor* processor, StateStep from) {
    Serial.println("Entering resistor check state");

  blinker.appendBlinkTask(processor->thisStateBlinkTask);
}

void resistorCheckExit(StateProcessor* processor) {
  Serial.println("Resistor check exit");
}

StateProcessor* ResistorCheckStateProcessor() {
  StateProcessor* processor = new StateProcessor{
    RESISTOR_CHECK,
    {RESISTOR_CHECK, BLINK_LENGTH, BLINK_DELAY, true, 1000},
    resistorCheckEnter,
    resistorCheckExit
  };

  return processor;
}