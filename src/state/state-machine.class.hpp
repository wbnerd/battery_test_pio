#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

#include "state/state-step.enum.hpp"
#include "state/state-processor.struct.hpp"

class StateMachine {
  public:
    static void init();
    static void iterate();

  private:
    static StateProcessor* currentState;
    static void changeState(StateStep state);
    static StateStep exitCurrentState();
    static StateStep enterToState(StateStep state);
};

#endif