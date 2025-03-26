#include <blink/blink.class.hpp>
#include "state-processors.hpp"
#include <constants.hpp>
#include "di/di.hpp"
#include "sensor/sensor.class.hpp"
#include "relay/relay.class.hpp"
#include "resistor/resistor.class.hpp"
#include "logs/logger.hpp"

StateStep resistorCheckEnter(StateProcessor* processor) {
  auto relay = Container<Relay>::get();
  auto sensor = Container<Sensor>::get();

  relay->on();

  delay(100);

  auto status = sensor->readSensor();

  if (abs(status->current) < 0.001) { // Less than 1mA
    relay->off();
    return StateStep::RESISTOR_REQUEST;
  }

  float resistorValue = status->shuntVoltage / status->current;

  Container<Resistor>::set(new Resistor(resistorValue));

  char buffer[32];
  sprintf(buffer, "Resistor value: %.2f ohms", resistorValue);
  Logger::log(buffer);

  // Turn off relay
  relay->off();

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