#include <blink/blink.class.hpp>
#include "state-processors.hpp"
#include <constants.hpp>

void testEndEnter(StateProcessor* processor, StateStep from) {
  Serial.println("Test end initiated");

  blinker.appendBlinkTask(processor->blinkTask);
}

void testEndExit(StateProcessor* processor) {
  Serial.println("Test end state exit");
}

StateProcessor* TestEndStateProcessor() {
  StateProcessor* processor = new StateProcessor{
    TEST_END,
    {TEST_END, BLINK_LENGTH, BLINK_DELAY, true, 1000},
    testEndEnter,
    testEndExit
  };

  return processor;
}