#include "di/container.class.hpp"
#include "state/state-step.enum.hpp"
#include "state/state-processor-fabric.hpp"
#include "state/state-processor-abstract.hpp"
#include "state-machine.class.hpp"
#include "state/state-step.enum.hpp"
#include "logs/logger.hpp"

StateProcessor* StateMachine::currentState = nullptr;
StateStep StateMachine::nextState = StateStep::START;
StateMachinePosition StateMachine::currentPosition = StateMachinePosition::ITERATE;

void StateMachine::init() {
  currentPosition = StateMachinePosition::ITERATE;
  currentState = stateProcessorFabric(StateStep::START);
}

void StateMachine::iterate() {
  char buffer[32];

  if (currentPosition == StateMachinePosition::EXIT)
  {
    if (currentState == nullptr) {
      Logger::log("Current state is null");
      currentPosition = StateMachinePosition::ENTER;
      return;
    }

    auto exitingState = currentState->thisState;

    sprintf(buffer, "try exit current state: %d", exitingState);
    Logger::log(buffer);

    auto exitResultState = exitCurrentState();

    sprintf(buffer, "exit result: %d", exitResultState);
    Logger::log(buffer);

    if (exitResultState != exitingState)
    {
      planChangeState(exitResultState);
      return;
    }

    currentPosition = StateMachinePosition::ENTER;
    return;
  }

  if (currentPosition == StateMachinePosition::ENTER)
  {
    sprintf(buffer, "try enter state: %d", nextState);
    Logger::log(buffer);
    auto enterState = enterToState(nextState);
    sprintf(buffer, "enter state result: %d", enterState);
    Logger::log(buffer);

    if (enterState != nextState)
    {
      planChangeState(enterState);
      return;
    }

    nextState = StateStep::START;
    currentPosition = StateMachinePosition::ITERATE;
    return;
  }

  if (currentPosition == StateMachinePosition::ITERATE)
  {
    if (currentState == nullptr) {
      planChangeState(StateStep::STATE_MACHINE_ERROR);
      return;
    }

    auto responseState = currentState->iterate(currentState);

    if (responseState != currentState->thisState) {
      planChangeState(responseState);
    }
  }
}

void StateMachine::planChangeState(StateStep toState) {
    char buffer[32];
    sprintf(buffer, "changing state to: %d", toState);
    Logger::log(buffer);

    nextState = toState;
    currentPosition = StateMachinePosition::EXIT;
}

StateStep StateMachine::exitCurrentState() {
  auto stateStepExiting = currentState->thisState;
  abstractStateExit(currentState);

  if (currentState->exit != nullptr)
  {
    auto exitResult = currentState->exit(currentState);
    delete currentState;
    currentState = nullptr;
    return exitResult;
  }

  delete currentState;
  currentState = nullptr;

  return stateStepExiting;
}

StateStep StateMachine::enterToState(StateStep state) {
  StateProcessor* newState = stateProcessorFabric(state);

  abstractStateEnter(newState);

  currentState = newState;

  if (newState->enter != nullptr)
  {
    return newState->enter(currentState);
  }

  return newState->thisState;
}