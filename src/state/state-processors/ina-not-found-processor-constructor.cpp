#include "state-processors.hpp"
#include <constants.hpp>
#include "di/di.hpp"
#include "display/display.class.hpp"
#include "logs/logger.hpp"

StateStep inaNotFoundStart(StateProcessor* processor) {
  auto display = Container<Display>::get();

  auto message = F("i2c cur sensor not found");
  auto message2 = F("check and reboot");

  display->startScreen(message);
  display->appendScreenMessage(message2);
  Logger::log(message);
  Logger::log(message2);

  return StateStep::INA_NOT_FOUND;
}

StateProcessor* InaNotFoundStateProcessor() {
  StateProcessor* processor = new StateProcessor{
    StateStep::INA_NOT_FOUND,
    {StateStep::INA_NOT_FOUND, BLINK_LENGTH, BLINK_DELAY, true, 1000},
    inaNotFoundStart,
    nullptr,
    nullptr,
  };

  return processor;
}