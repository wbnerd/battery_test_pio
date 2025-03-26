#include <blink/blink.class.hpp>
#include "state-processors.hpp"
#include <constants.hpp>

StateStep readyForTestEnter(StateProcessor* processor) {

  // oled.print("Тест до ");
  // oled.print("Калиб. U ");
  // oled.print(" I ");
  // Serial.print("   Calibration I: ");
  // Serial.println(calibrI);

  // Serial.println("  h:m:s   V     mA  mWh mAh");
  return StateStep::READY_FOR_TEST;
}

StateProcessor* ReadyForTestStateProcessor() {
  return new StateProcessor{
    READY_FOR_TEST,
    {READY_FOR_TEST, BLINK_LENGTH, BLINK_DELAY, true, 1000},
    readyForTestEnter,
    nullptr,
    nullptr,
  };
}
