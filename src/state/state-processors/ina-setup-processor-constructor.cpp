#include "state-processors.hpp"
#include <constants.hpp>
#include <GyverINA.h>
#include "di/container.class.hpp"
#include "sensor/sensor.class.hpp"

StateStep inaSetupIterate(StateProcessor* processor) {
  if (!Sensor::testConnection()) {
    return StateStep::INA_NOT_FOUND;
  }

  Container<Sensor>::set(new Sensor());

  return StateStep::BATTERY_CHECK;
}

StateProcessor* InaSetupStateProcessor() {
  StateProcessor* processor = new StateProcessor{
    StateStep::INA_SETUP,
    {StateStep::INA_SETUP, BLINK_LENGTH, BLINK_DELAY, true, 1000},
    nullptr,
    nullptr,
    inaSetupIterate
  };

  return processor;
}