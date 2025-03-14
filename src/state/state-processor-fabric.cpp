#include "state-processor-fabric.hpp"
#include "./state-processors/state-processors.hpp"

StateProcessor* stateProcessorFabric(StateStep step) {
  switch (step)
  {
  case START:
    return StartStateProcessor();

  case WIFI_SETUP:
    return WifiSetupStateProcessor();

  case GPIO_SETUP:
    return GpioSetupStateProcessor();

  case OLED_SETUP:
    return OledSetupStateProcessor();

  case INA_SETUP:
    return InaSetupStateProcessor();

  case BATTERY_CHECK:
    return BatteryCheckStateProcessor();

  case BATTERY_REQUEST:
    return BatteryRequestStateProcessor();

  case BATTERY_ERROR:
    return BatteryErrorStateProcessor();

  case RESISTOR_CHECK:
    return ResistorCheckStateProcessor();

  case RESISTOR_REQUEST:
    return ResistorRequestStateProcessor();

  case RESISTOR_ERROR:
    return ResistorErrorStateProcessor();

  case READY_FOR_TEST:
    return ReadyForTestStateProcessor();

  case TEST:
    return TestStateProcessor();

  case TEST_ERROR:
    return TestErrorStateProcessor();

  case TEST_END:
    return TestEndStateProcessor();

  case TEST_RESULT:
    return TestResultStateProcessor();

  default:
    return StateMachineErrorStateProcessor();
  }
}