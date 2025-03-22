#include "di/di.hpp"
#include "state/state-step.enum.hpp"
#include "state/state-processor-fabric.hpp"
#include "state/state-processor-abstract.hpp"
#include "state-machine.class.hpp"

void StateMachine::init() {
  currentState = stateProcessorFabric(StateStep::START);
}

void StateMachine::iterate() {
  if (currentState != nullptr && currentState->iterate != nullptr) {
    auto responseState = currentState->iterate(currentState);

    if (responseState != currentState->thisState) {
      changeState(responseState);
    }
  }
}

// static StateProcessor* currentState;

void StateMachine::changeState(StateStep state) {
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

StateStep StateMachine::exitCurrentState() {
  abstractStateExit(currentState);

  if (currentState->exit != nullptr)
  {
    return currentState->exit(currentState);
  }

  return currentState->thisState;
}

StateStep StateMachine::enterToState(StateStep state) {
  StateProcessor* newState = stateProcessorFabric(state);

  abstractStateEnter(newState);

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