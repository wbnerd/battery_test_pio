#include <blink/blink.class.hpp>
#include "state-processors.hpp"
#include <constants.hpp>

void gpioSetupEnter(StateProcessor* processor, StateStep from) {
  Serial.println();
  Serial.println("Gpio port set");

  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);

  blinker.appendBlinkTask(processor->thisStateBlinkTask);
}

void gpioSetupExit(StateProcessor* processor) {
  Serial.println("GPIO exit");
}

StateProcessor* GpioSetupStateProcessor() {
  StateProcessor* processor = new StateProcessor{
    GPIO_SETUP,
    {GPIO_SETUP, BLINK_LENGTH, BLINK_DELAY, true, 1000},
    gpioSetupEnter,
    gpioSetupExit
  };

  return processor;
}