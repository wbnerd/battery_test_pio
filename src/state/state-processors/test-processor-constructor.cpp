#include <blink/blink.class.hpp>
#include "state-processors.hpp"
#include <constants.hpp>
#include <di/container.class.hpp>
#include <display/display.class.hpp>
#include <load/load.class.hpp>
#include <batteries/batteries.hpp>
#include <sensor/sensor.class.hpp>
#include <relay/relay.class.hpp>
#include <logs/logger.hpp>

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
const float secondsInHour = 3600;
const float measurementDelay = 100;
const float displayUpdateDelay = 1500;
static unsigned long startTime = 0;
static unsigned long lastMeasurementTime = 0;
static unsigned long lastDisplayUpdateTime = 0;
static float mah = 0;
static float mwh = 0;

StateStep testEnter(StateProcessor* processor) {
  auto display = Container<Display>::get();
  display->setupParameterScreen(F("Test In Progress"), 10, paramNames);

  auto load = Container<Load>::get();
  auto battery = Container<BatteryDescription>::get();

  float parameters[10] = {
    0, // "Ub  ",
    0, // "Ir  ",
    0, // "mAh ",
    0, // "mWh ",
    battery->startVoltage, // "Ust ",
    battery->lowVoltage, // "Umin",
    0, // "Ucal",
    0, // "Ical",
    0, // "T   ",
    load->getValue(), // "Rl  "
  };

  display->updateParameterScreen(parameters);

  auto relay = Container<Relay>::get();
  relay->on();
  delay(RELAY_RELEASE_TIME);

  startTime = millis();
  return StateStep::TEST;
}

StateStep testExit(StateProcessor* processor) {
  auto relay = Container<Relay>::get();
  relay->off();
  return StateStep::TEST;
}

StateStep testIterate(StateProcessor* processor) {
  auto timeStamp = millis() - startTime;
  auto timeFromLastMeasurement = timeStamp - lastMeasurementTime;

  if (timeFromLastMeasurement < measurementDelay) {
    return StateStep::TEST;
  }

  auto sensor = Container<Sensor>::get();
  lastMeasurementTime = timeStamp;
  auto load = Container<Load>::get();
  auto battery = Container<BatteryDescription>::get();
  auto display = Container<Display>::get();

  auto sensorStatus = sensor->readSensor();

  float secondsFromLastMeasurement = timeFromLastMeasurement / 1000.0f;
  float hourFrame = secondsFromLastMeasurement / secondsInHour;

  mah = mah + (sensorStatus->current * hourFrame);
  mwh = mwh + (sensorStatus->current * hourFrame * sensorStatus->batteryVoltage);

  char buffer[32];

  sprintf(buffer, "hourFrame %f", (sensorStatus->current * hourFrame));
  Logger::log(buffer);

  Serial.print(timeStamp);
  Serial.print(" ");
  Serial.print(sensorStatus->batteryVoltage, 4); //напряжение, 4 знака после запятой
  Serial.print(" ");
  Serial.print(sensorStatus->current, 2); //ток, 2 знака после запятой
  Serial.print(" ");
  Serial.print(mwh, 1); //энергия, 1 знак после запятой
  Serial.print(" ");
  Serial.println(mah, 1); //ёмкость, 1 знак после запятой

  if (timeStamp < lastDisplayUpdateTime + displayUpdateDelay) {
    delete sensorStatus;

    return StateStep::TEST;
  }

  lastDisplayUpdateTime = timeStamp;

  float parameters[10] = {
    sensorStatus->batteryVoltage, // "Ub  ",
    sensorStatus->current, // "Ir  ",
    mah, // "mAh ",
    mwh, // "mWh ",
    battery->startVoltage, // "Ust ",
    battery->lowVoltage, // "Umin",
    sensor->calibrI, // "Ucal",
    sensor->calibrU, // "Ical",
    timeStamp / 1000, // "T   ",
    load->getValue(), // "Rl  "
  };

  display->updateParameterScreen(parameters);

  delete sensorStatus;

  return StateStep::TEST;
}

StateProcessor* TestStateProcessor() {
  StateProcessor* processor = new StateProcessor{
    TEST,
    {TEST, BLINK_LENGTH, BLINK_DELAY, true, 1000},
    testEnter,
    testExit,
    testIterate,
  };

  return processor;
}
