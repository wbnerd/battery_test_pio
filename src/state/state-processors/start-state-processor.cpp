#include <blink/blink.class.hpp>
#include "state-processors.hpp"
#include <constants.hpp>

StateProcessor* StartStateProcessor() {
  StateProcessor* processor = new StateProcessor{
    GPIO_SETUP,
    {GPIO_SETUP, BLINK_LENGTH, BLINK_DELAY, true, 1000},
    nullptr,
    nullptr,
    nullptr
  };

  return processor;
}