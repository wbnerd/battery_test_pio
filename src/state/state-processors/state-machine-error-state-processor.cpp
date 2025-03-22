#include "state-processors.hpp"

StateProcessor* StateMachineErrorStateProcessor() {
  return new StateProcessor{
    STATE_MACHINE_ERROR,
    {0, 50, 50, false, 0},
    nullptr,
    nullptr,
    nullptr
  };
}