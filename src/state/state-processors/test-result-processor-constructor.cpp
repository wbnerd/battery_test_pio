#include <blink/blink.class.hpp>
#include "state-processors.hpp"
#include <constants.hpp>

void testResultEnter(StateProcessor* processor, StateStep from) {
  Serial.println("Test result initiated");

  blinker.appendBlinkTask(processor->blinkTask);
}

void testResultExit(StateProcessor* processor) {
  Serial.println("Test result exit");
}

StateProcessor* TestResultStateProcessor() {
  StateProcessor* processor = new StateProcessor{
    TEST_RESULT,
    {TEST_RESULT, BLINK_LENGTH, BLINK_DELAY, true, 1000},
    testResultEnter,
    testResultExit
  };

  return processor;
}