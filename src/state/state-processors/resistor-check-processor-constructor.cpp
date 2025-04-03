#include <blink/blink.class.hpp>
#include "state-processors.hpp"
#include <constants.hpp>
#include "di/container.class.hpp"
#include "sensor/sensor.class.hpp"
#include "relay/relay.class.hpp"
#include "load/load.class.hpp"
#include "logs/logger.hpp"

StateStep resistorCheckEnter(StateProcessor* processor) {
  auto relay = Container<Relay>::get();
  auto sensor = Container<Sensor>::get();

  relay->on();

  delay(RELAY_RELEASE_TIME);

  SensorStatus status;
  sensor->readSensor(status);

  relay->off();

  char buffer[32];
  sprintf(buffer, "Current: %.3f", status.current);
  Logger::log(buffer);
  sprintf(buffer, "VoltageS: %.3f", status.shuntVoltage);
  Logger::log(buffer);
  sprintf(buffer, "VoltageB: %.3f", status.batteryVoltage);
  Logger::log(buffer);

  if (abs(status.current) < 1.0) { // Less than 1mA
    return StateStep::RESISTOR_REQUEST;
  }

  float resistorValue = (status.batteryVoltage / (status.current / 1000)) - 0.1;

  if (resistorValue < 10) {
    return StateStep::RESISTOR_REQUEST;
  }

  Container<Load>::set(new Load(resistorValue));

  sprintf(buffer, "Resistor value: %.3f ohms", resistorValue);
  Logger::log(buffer);

  return StateStep::READY_FOR_TEST;
}

StateProcessor* ResistorCheckStateProcessor() {
  StateProcessor* processor = new StateProcessor{
    RESISTOR_CHECK,
    {RESISTOR_CHECK, BLINK_LENGTH, BLINK_DELAY, true, 1000},
    resistorCheckEnter,
    nullptr,
    nullptr,
  };

  return processor;
}