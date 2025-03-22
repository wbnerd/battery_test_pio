#include <Arduino.h>

#include "di/di.hpp"
#include "logs/logger.hpp"
#include "blink/blink.class.hpp"
#include "constants.hpp"
#include "state/state-machine.class.hpp"
#include "button/button.class.hpp"

// unsigned long startMillis; //Время в момент начала измерения
// unsigned long MillisTake; //Время следующего измерения
// unsigned long MillisCom; //Время следующего вывода в COM-порт
// unsigned long seconds;
// unsigned long minutes;
// unsigned long hours;
// float U; //напряжение в вольтах
// float I; //ток в миллиамперах
// float mwh = 0; //милливатт-часы
// float mah = 0; //миллиампер-часы
// float Ustop = 0.9; //Напряжение остановки измерения в вольтах.
// int animacount = 20; //количество миганий дохлой батарейкой до снижения яркости

void setup() {
  delay(500); //Задержка для стабилизации питания

  Serial.begin(SERIAL_SPEED);
  Serial.println();
  Serial.println("Serial setup initiated");

  Container<Logger>::set(new Logger());
  Container<Blink>::set(new Blink(LED_BUILTIN, LOW));
  Container<Button>::set(new Button());

  StateMachine::init();
}

void loop(void) {
  StateMachine::iterate();
}
