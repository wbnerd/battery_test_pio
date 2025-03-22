#include <blink/blink.class.hpp>
#include "state-processors.hpp"
#include "state/state-step.enum.hpp"
#include <constants.hpp>

StateStep startStateProcessorIterate(StateProcessor* processor) {
  return StateStep::WIFI_SETUP;
}

StateProcessor* StartStateProcessor() {
  return new StateProcessor{
    StateStep::START,
    {0, 50, 500, false, 0},
    nullptr,
    nullptr,
    startStateProcessorIterate
  };
}