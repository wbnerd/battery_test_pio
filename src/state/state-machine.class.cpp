#include "di/di.hpp"
#include "state/state-step.enum.hpp"
#include "state/state-processor-fabric.hpp"
#include "state/state-processor-abstract.hpp"

class StateMachine {
  public:
    static void init() {
      currentState = stateProcessorFabric(StateStep::START);
    }

    static void iterate() {
      if (currentState != nullptr) {
        auto responseState = currentState->iterate(currentState);

        if (responseState != currentState->thisState) {
          changeState(responseState);
        }
      }
    }

  private:
    static StateProcessor* currentState;

    static void changeState(StateStep state) {
      auto exitState = exitCurrentState();

      if (exitState != currentState->thisState)
      {
        changeState(exitState);
        return;
      }

      auto enterState = enterToState(state);

      if (enterState != state)
      {
        changeState(enterState);
      }
    }

    static StateStep exitCurrentState() {
      abstractStateExit(currentState);

      if (currentState->exit != nullptr)
      {
        return currentState->exit(currentState);
      }

      return currentState->thisState;
    }

    static StateStep enterToState(StateStep state) {
      StateProcessor* newState = stateProcessorFabric(state);

      abstractStateEnter(newState, currentState->thisState);

      if (newState->enter != nullptr)
      {
        auto enterState = newState->enter(currentState);

        if (enterState != newState->thisState)
        {
          return enterState;
        }
      }

      delete currentState;
      currentState = newState;

      return newState->thisState;
    }
};