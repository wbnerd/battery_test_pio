#include <blink/blink.class.hpp>
#include "state-processors.hpp"
#include <constants.hpp>

void testErrorEnter(StateProcessor* processor, StateStep from) {
  Serial.println();
  Serial.println("Test error initiated");

  blinker.appendBlinkTask(processor->thisStateBlinkTask);
}

void testErrorExit(StateProcessor* processor) {
  Serial.println("Test error exit");
}

StateProcessor* TestErrorStateProcessor() {
  StateProcessor* processor = new StateProcessor{
    TEST_ERROR,
    {TEST_ERROR, BLINK_LENGTH, BLINK_DELAY, true, 1000},
    testErrorEnter,
    testErrorExit
  };

  return processor;
}
