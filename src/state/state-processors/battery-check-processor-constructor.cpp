#include <blink/blink.class.hpp>
#include "state-processors.hpp"
#include <constants.hpp>
#include "di/di.hpp"
#include "sensor/sensor.class.hpp"
#include "batteries/batteries.hpp"

StateStep batteryCheckEnter(StateProcessor* processor) {
  auto sensor = Container<Sensor>::get();
  auto description = new BatteryDescription();
  auto status = sensor->readSensor();
  auto batteryVoltage = status->batteryVoltage;

  if (batteryVoltage > 15) {
    return StateStep::BATTERY_ERROR;
  } else if (batteryVoltage > 10.5) {
    description->lowVoltage = 10.5;
    description->name = "PB";
  } else if (batteryVoltage > 5.4) {
    description->lowVoltage = 5.4;
    description->name = "9V";
  } else if (batteryVoltage > 3.3) {
    description->lowVoltage = 3.3;
    description->name = "Li";
  } else if (batteryVoltage > 2) {
    description->lowVoltage = 2;
    description->name = "3V";
  } else if (batteryVoltage > 0.9) {
    description->lowVoltage = 0.9;
    description->name = "AA";
  } else {
    return StateStep::BATTERY_REQUEST;
  }

  Container<BatteryDescription>::set(description);

  return StateStep::RESISTOR_CHECK;
}

StateProcessor* BatteryCheckStateProcessor() {
  StateProcessor* processor = new StateProcessor{
    StateStep::BATTERY_CHECK,
    {StateStep::BATTERY_CHECK, BLINK_LENGTH, BLINK_DELAY, true, 1000},
    batteryCheckEnter,
    nullptr,
    nullptr,
  };

  return processor;
}