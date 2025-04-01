#include <blink/blink.class.hpp>
#include "state-processors.hpp"
#include <constants.hpp>
#include <display/display.class.hpp>
#include "di/di.hpp"
#include <button/button.class.hpp>
StateStep readyForTestEnter(StateProcessor* processor) {
  auto display = Container<Display>::get();
  auto button = Container<Button>::get();
  button->set();

  char paramNames[][5] = {
    "Ub",
    "Ir",
    "mAh",
    "mWh",
    "Ust",
    "Umin",
    "Ucal",
    "Ical",
    "T"
  };

  display->setupParameterScreen(F("Press for Test"), 9, paramNames);

  return StateStep::READY_FOR_TEST;
}

StateStep readyForTestIterate(StateProcessor* processor) {
  auto button = Container<Button>::get();

  if (button->isTriggered()) {
    return StateStep::TEST;
  }

  return StateStep::READY_FOR_TEST;
}

StateStep readyForTestExit(StateProcessor* processor) {
  auto button = Container<Button>::get();
  button->unset();

  auto display = Container<Display>::get();
  display->clearScreen();

  return StateStep::READY_FOR_TEST;
}

StateProcessor* ReadyForTestStateProcessor() {
  return new StateProcessor{
    READY_FOR_TEST,
    {READY_FOR_TEST, BLINK_LENGTH, BLINK_DELAY, true, 1000},
    readyForTestEnter,
    readyForTestIterate,
    readyForTestExit,
  };
}
