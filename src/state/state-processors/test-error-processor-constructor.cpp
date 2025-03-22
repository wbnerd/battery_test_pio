#include <blink/blink.class.hpp>
#include "state-processors.hpp"
#include <constants.hpp>

StateStep testErrorEnter(StateProcessor* processor) {
  return StateStep::TEST_ERROR;
}

StateProcessor* TestErrorStateProcessor() {
  StateProcessor* processor = new StateProcessor{
    TEST_ERROR,
    {TEST_ERROR, BLINK_LENGTH, BLINK_DELAY, true, 1000},
    testErrorEnter,
    nullptr,
    nullptr
  };

  return processor;
}
