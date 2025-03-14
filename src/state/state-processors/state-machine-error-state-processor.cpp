#include "state-processors.hpp"

StateProcessor* StateMachineErrorStateProcessor() {
  StateProcessor* processor = new StateProcessor{
    STATE_MACHINE_ERROR,
    {0, 50, 50, false, 0},
    nullptr,
    nullptr,
    nullptr
  };
}