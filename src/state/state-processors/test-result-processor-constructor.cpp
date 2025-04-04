#include <blink/blink.class.hpp>
#include "state-processors.hpp"
#include <constants.hpp>
#include <di/container.class.hpp>
#include "batteries/batteries.hpp"
#include "display/display.class.hpp"

StateStep testResultEnter(StateProcessor* processor) {
  auto battery = Container<BatteryDescription>::get();
  auto display = Container<Display>::get();
  char buffer[32];

  sprintf(buffer, "Test Result %s battery", battery->startVoltage);
  display->startScreen(buffer);

  sprintf(buffer, "Start Voltage: %f", battery->startVoltage);
  display->appendScreenMessage(buffer);

  sprintf(buffer, "Low Voltage: %f", battery->lowVoltage);
  display->appendScreenMessage(buffer);

  sprintf(buffer, "mWh: %f", battery->mwh);
  display->appendScreenMessage(buffer);

  sprintf(buffer, "mAh: %f", battery->mah);
  display->appendScreenMessage(buffer);

  return StateStep::TEST_RESULT;
}

StateStep testResultIterate(StateProcessor* processor) {
  return StateStep::TEST_RESULT;
}

StateProcessor* TestResultStateProcessor() {
  StateProcessor* processor = new StateProcessor{
    TEST_RESULT,
    {TEST_RESULT, BLINK_LENGTH, BLINK_DELAY, true, 1000},
    testResultEnter,
    nullptr,
    testResultIterate,
  };

  return processor;
}