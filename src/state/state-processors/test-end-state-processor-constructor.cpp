#include <blink/blink.class.hpp>
#include "state-processors.hpp"
#include <constants.hpp>

StateStep testEndEnter(StateProcessor* processor) {
  return StateStep::TEST_END;
}

StateProcessor* TestEndStateProcessor() {
  StateProcessor* processor = new StateProcessor{
    TEST_END,
    {TEST_END, BLINK_LENGTH, BLINK_DELAY, true, 1000},
    testEndEnter,
    nullptr,
    nullptr,
  };

  return processor;
}