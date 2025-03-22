#include <blink/blink.class.hpp>
#include "state-processors.hpp"
#include <constants.hpp>

StateStep testResultEnter(StateProcessor* processor) {
  return StateStep::TEST_RESULT;
}

StateProcessor* TestResultStateProcessor() {
  StateProcessor* processor = new StateProcessor{
    TEST_RESULT,
    {TEST_RESULT, BLINK_LENGTH, BLINK_DELAY, true, 1000},
    testResultEnter,
    nullptr,
    nullptr,
  };

  return processor;
}