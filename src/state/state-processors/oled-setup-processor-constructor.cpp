#include <blink/blink.class.hpp>
#include "state-processors.hpp"
#include <constants.hpp>
#include "di/di.hpp"
#include "display/display.class.hpp"
#include "button/button.class.hpp"

StateStep oledSetupEnter(StateProcessor* processor) {
  auto display = new Display();
  Container<Display>::set(display);
  display->startScreen(F("Screen initiated Test:"));
  display->appendScreenMessage(F("012345678901234567890123456789"));
  display->appendScreenMessage(F("012345678901234567890123456789"));
  display->appendScreenMessage(F("012345678901234567890123456789"));
  display->appendScreenMessage(F("012345678901234567890123456789"));
  display->appendScreenMessage(F("012345678901234567890123456789"));
  display->appendScreenMessage(F("012345678901234567890123456789"));
  display->appendScreenMessage(F("Press button to preceeeeeed"));

  auto button = Container<Button>::get();
  button->set();

  return StateStep::OLED_SETUP;
}

StateStep oledSetupIterate(StateProcessor* processor) {
  auto button = Container<Button>::get();

  if (button->isTriggered())
  {
    return StateStep::INA_SETUP;
  }

  return StateStep::OLED_SETUP;
}

StateStep oledSetupExit(StateProcessor* processor) {
  auto button = Container<Button>::get();
  button->unset();

  return StateStep::OLED_SETUP;
}

StateProcessor* OledSetupStateProcessor() {
  StateProcessor* processor = new StateProcessor{
    StateStep::OLED_SETUP,
    {StateStep::OLED_SETUP, BLINK_LENGTH, BLINK_DELAY, true, 1000},
    oledSetupEnter,
    nullptr,
    oledSetupIterate
  };

  return processor;
}