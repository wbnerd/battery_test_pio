#include "di/di.hpp"
#include "state/state-step.enum.hpp"
#include "state/state-processor-fabric.hpp"
#include "state/state-processor-abstract.hpp"

class StateMachine {
  public:
    static void init() {

    }

    static void iterate() {


    }

  private:
    static StateProcessor* currentState;

    static void changeState(StateStep state) {
      abstractStateExit(currentState);

      if (currentState->exit != nullptr)
      {
        currentState->exit(currentState);
      }

      StateProcessor* newState = stateProcessorFabric(state);

      abstractStateEnter(newState, currentState->thisState);

      if (newState->enter != nullptr)
      {
        newState->enter(newState, currentState->thisState);
      }

      delete currentState;
      currentState = newState;
    }

    static void exitState(StateStep state) {
    }

};