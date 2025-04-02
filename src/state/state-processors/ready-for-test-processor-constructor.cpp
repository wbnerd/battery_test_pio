#include <blink/blink.class.hpp>
#include "state-processors.hpp"
#include <constants.hpp>
#include <display/display.class.hpp>
#include "di/container.class.hpp"
#include <button/button.class.hpp>
#include <load/load.class.hpp>
#include <batteries/batteries.hpp>
#include <sensor/sensor.class.hpp>

const char paramNames[10][5] = {
    "Ub  ",
    "Ir  ",
    "mAh ",
    "mWh ",
    "Ust ",
    "Umin",
    "Ucal",
    "Ical",
    "T   ",
    "Rl  "
  };

StateStep readyForTestEnter(StateProcessor* processor) {
  auto display = Container<Display>::get();
  auto button = Container<Button>::get();
  auto sensor = Container<Sensor>::get();
  button->set();

  display->setupParameterScreen(F("Press for Test"), 10, paramNames);

  auto load = Container<Load>::get();
  auto battery = Container<BatteryDescription>::get();

  float parameters[10] = {
    0, // "Ub  ",
    0, // "Ir  ",
    0, // "mAh ",
    0, // "mWh ",
    battery->startVoltage, // "Ust ",
    battery->lowVoltage, // "Umin",
    sensor->calibrI, // "Ucal",
    sensor->calibrU, // "Ical",
    0, // "T   ",
    load->getValue(), // "Rl  "
  };

  display->updateParameterScreen(parameters);

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
    readyForTestExit,
    readyForTestIterate,
  };
}
