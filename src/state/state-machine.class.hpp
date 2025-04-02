#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

#include "state/state-step.enum.hpp"
#include "state/state-processor.struct.hpp"
#include "state/state-machine-positions.enum.hpp"

class StateMachine {
  public:
    static void init();
    static void iterate();

  private:
    static StateProcessor* currentState;
    static StateMachinePosition currentPosition;
    static StateStep nextState;

    static void planChangeState(StateStep toState);

    static StateStep exitCurrentState();
    static StateStep enterToState(StateStep state);
};

#endif