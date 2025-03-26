#include <blink/blink.class.hpp>
#include "state-processors.hpp"
#include <constants.hpp>
#include "di/di.hpp"
#include "display/display.class.hpp"
#include "button/button.class.hpp"

StateStep resistorRequestEnter(StateProcessor* processor) {
  auto button = Container<Button>::get();
  button->set();

  auto display = Container<Display>::get();

  display->startScreen(F("Shunt not detected"));
  display->appendScreenMessage(F("Install resistor"));
  display->appendScreenMessage(F("And press button"));

  return StateStep::RESISTOR_REQUEST;
}

StateStep resistorRequestExit(StateProcessor* processor) {
  auto button = Container<Button>::get();
  button->unset();

  auto display = Container<Display>::get();
  display->clearScreen();

  return StateStep::RESISTOR_REQUEST;
}

StateStep resistorRequestIterate(StateProcessor* processor) {
  auto button = Container<Button>::get();

  if (button->isTriggered()) {
    return StateStep::RESISTOR_CHECK;
  }

  return StateStep::RESISTOR_REQUEST;
}

StateProcessor* ResistorRequestStateProcessor() {
  StateProcessor* processor = new StateProcessor{
    RESISTOR_REQUEST,
    {RESISTOR_REQUEST, BLINK_LENGTH, BLINK_DELAY, true, 1000},
    resistorRequestEnter,
    resistorRequestExit,
    resistorRequestIterate
  };

  return processor;
}