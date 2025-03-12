#include <blink/blink.class.hpp>
#include "state-processors.hpp"
#include <constants.hpp>

void serialSetupEnter(StateProcessor* processor, StateStep from) {
  Serial.begin(SERIAL_SPEED);
  Serial.println();
  Serial.println("Serial setup initiated");

  blinker.appendBlinkTask(processor->thisStateBlinkTask);
}

void serialSetupExit(StateProcessor* processor) {
  Serial.println("Serial setup exit");
}

StateProcessor* SerialSetupStateProcessor() {
  StateProcessor* processor = new StateProcessor{
    SERIAL_SETUP,
    {SERIAL_SETUP, BLINK_LENGTH, BLINK_DELAY, true, 1000},
    serialSetupEnter,
    serialSetupExit
  };

  return processor;
}