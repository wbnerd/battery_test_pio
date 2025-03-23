#include "di/di.hpp"
#include "state/state-step.enum.hpp"
#include "state/state-processor-fabric.hpp"
#include "state/state-processor-abstract.hpp"
#include "state-machine.class.hpp"
#include "state/state-step.enum.hpp"
#include "logs/logger.hpp"

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

StateProcessor* StateMachine::currentState = nullptr;

void StateMachine::changeState(StateStep state) {
  char buffer[32];
  sprintf(buffer, "changing state to: %d", state);
  Logger::log(buffer);

  sprintf(buffer, "try exit current state: %d", currentState->thisState);
  Logger::log(buffer);
  auto exitState = exitCurrentState();

  sprintf(buffer, "exit result: %d", exitState);
  Logger::log(buffer);

  if (exitState != currentState->thisState)
  {
    changeState(exitState);
    return;
  }

  sprintf(buffer, "try enter state: %d", state);
  auto enterState = enterToState(state);
  Logger::log(buffer);
  sprintf(buffer, "enter state result: %d", enterState);
  Logger::log(buffer);

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
      delete newState;
      return enterState;
    }
  }

  delete currentState;
  currentState = newState;

  return newState->thisState;
}