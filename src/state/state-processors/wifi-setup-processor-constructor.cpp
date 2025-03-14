#include <blink/blink.class.hpp>
#include "state-processors.hpp"
#include <constants.hpp>
#include <ESP8266WiFi.h>

void wifiSetupEnter(StateProcessor* processor, StateStep from) {
//Отключение WiFi. убрать, если используется плата без Wi-Fi
  WiFi.mode(WIFI_OFF);
  WiFi.forceSleepBegin();

  Serial.println();
  Serial.println("WiFi setup initiated");

  blinker.appendBlinkTask(processor->blinkTask);
}

void wifiSetupExit(StateProcessor* processor) {
  Serial.println("WiFi setup exit");
}

StateProcessor* WifiSetupStateProcessor() {
  StateProcessor* processor = new StateProcessor{
    WIFI_SETUP,
    {WIFI_SETUP, BLINK_LENGTH, BLINK_DELAY, true, 1000},
    wifiSetupEnter,
    wifiSetupExit
  };

  return processor;
}