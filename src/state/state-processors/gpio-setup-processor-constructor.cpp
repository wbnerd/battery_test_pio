#include <blink/blink.class.hpp>
#include "state-processors.hpp"
#include <constants.hpp>

StateStep gpioSetupIterate(StateProcessor* processor) {
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);

  return StateStep::OLED_SETUP;
}

void gpioSetupExit(StateProcessor* processor) {
  Serial.println("GPIO exit");
}

StateProcessor* GpioSetupStateProcessor() {
  StateProcessor* processor = new StateProcessor{
    StateStep::GPIO_SETUP,
    {StateStep::GPIO_SETUP, BLINK_LENGTH, BLINK_DELAY, true, 1000},
    nullptr,
    nullptr,
    gpioSetupIterate,
  };

  return processor;
}