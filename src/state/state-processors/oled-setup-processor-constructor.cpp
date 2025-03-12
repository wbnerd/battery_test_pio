#include <blink/blink.class.hpp>
#include "state-processors.hpp"
#include <constants.hpp>
#include <GyverOLED.h>

GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;

void oledSetupEnter(StateProcessor* processor, StateStep from) {
  Serial.println();
  Serial.println("OLED setup initiated");

  oled.init(SDA_PIN, SCL_PIN);
  oled.clear();       // очистка
  oled.home();        // курсор в 0,0
  oled.setScale(1);   // масштаб текста (1..4)
  oled.print("BatteryTest");

  blinker.appendBlinkTask(processor->thisStateBlinkTask);
}

void oledSetupExit(StateProcessor* processor) {
  Serial.println("OLED setup exit");
}

StateProcessor* OledSetupStateProcessor() {
  StateProcessor* processor = new StateProcessor{
    OLED_SETUP,
    {OLED_SETUP, BLINK_LENGTH, BLINK_DELAY, true, 1000},
    oledSetupEnter,
    oledSetupExit
  };

  return processor;
}