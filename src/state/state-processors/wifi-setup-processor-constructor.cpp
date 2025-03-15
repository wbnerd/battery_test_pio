#include <blink/blink.class.hpp>
#include "state-processors.hpp"
#include <constants.hpp>
#include <ESP8266WiFi.h>

StateStep wifiSetupIterate(StateProcessor* processor) {
  WiFi.mode(WIFI_OFF);
  WiFi.forceSleepBegin();

  return StateStep::GPIO_SETUP;
}

StateProcessor* WifiSetupStateProcessor() {
  StateProcessor* processor = new StateProcessor{
    StateStep::WIFI_SETUP,
    {StateStep::WIFI_SETUP, BLINK_LENGTH, BLINK_DELAY, true, 1000},
    nullptr,
    nullptr,
    wifiSetupIterate,
  };

  return processor;
}