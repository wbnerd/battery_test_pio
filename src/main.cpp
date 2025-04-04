#include <Arduino.h>
#include "di/container.class.hpp"
#include "logs/logger.hpp"
#include "blink/blink.class.hpp"
#include "button/button.class.hpp"
#include "constants.hpp"
#include "state/state-machine.class.hpp"
#include "relay/relay.class.hpp"

void setup() {
  delay(500); //Задержка для стабилизации питания

  Serial.begin(SERIAL_SPEED);
  Serial.println();
  Serial.println("Serial setup initiated");

  Container<Blink>::set(new Blink(LED_BUILTIN, LOW));
  Container<Button>::set(new Button(BUTTON_PIN));
  Container<Relay>::set(new Relay(RELAY_PIN));

  StateMachine::init();
}

void loop(void) {
  StateMachine::iterate();
}
