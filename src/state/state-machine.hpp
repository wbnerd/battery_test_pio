#ifndef STATE_MACHINE_HPP
#define STATE_MACHINE_HPP

#include "state/state-step.enum.hpp"
#include "state/state-processor-abstract.hpp"

class StateMachine {
  public:
    static void init();
    static void iterate();

  private:
    static StateProcessor* currentState;
    static void changeState(StateStep state);
    static void exitState(StateStep state);
};

#endif