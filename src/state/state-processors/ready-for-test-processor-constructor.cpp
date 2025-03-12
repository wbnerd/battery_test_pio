#include <blink/blink.class.hpp>
#include "state-processors.hpp"
#include <constants.hpp>

void readyForTestEnter(StateProcessor* processor, StateStep from) {
  Serial.println();
  Serial.println("Ready for test initiated");

  blinker.appendBlinkTask(processor->thisStateBlinkTask);

  while (millis() < (premeterStart + 2600)) { // 3 секунды запускаем измерение каждые 0.5 сек
    delay(500); // Пауза между измерениями
    metering();
  }

  oled.clear();
  oled.setScale(1);
  oled.setCursor(0, 2);
  oled.print("Тест до ");
  oled.setCursor(50, 1);
  oled.setScale(2);
  oled.print(Ustop, 1);
  oled.print(" v");
  oled.setScale(1);
  oled.setCursor(0, 7);
  oled.print("Калиб. U ");
  oled.print(calibrU);
  oled.print(" I ");
  oled.print(calibrI);

  Serial.print("Test end voltage: ");
  Serial.print(Ustop, 1);
  Serial.print(" V");
  Serial.print("   Calibration U: ");
  Serial.print(calibrU);
  Serial.print("   Calibration I: ");
  Serial.println(calibrI);

  Serial.println("  h:m:s   V     mA  mWh mAh");
  datacom(); // Вывод первого значения в COM-порт



}

void readyForTestExit(StateProcessor* processor) {
  Serial.println("Ready for test exit");
}

StateProcessor* ReadyForTestStateProcessor() {
  StateProcessor* processor = new StateProcessor{
    READY_FOR_TEST,
    {READY_FOR_TEST, BLINK_LENGTH, BLINK_DELAY, true, 1000},
    readyForTestEnter,
    readyForTestExit
  };

  return processor;
}
