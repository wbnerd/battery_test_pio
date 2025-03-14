#include "state-processor-abstract.hpp"
#include "di/di.hpp"
#include "logs/logger.hpp"
#include "blink/blink.class.hpp"

void abstractStateEnter(StateProcessor* processor, StateStep from) {
  char buffer[16];
  sprintf(buffer, "state -> %d", processor->thisState);
  Container<Logger>::get()->log(buffer);

  Container<Blink>::get()->setupBlinkTask(processor->blinkTask);
}

void abstractStateExit(StateProcessor* processor) {
  char buffer[16];
  sprintf(buffer, "state != %d", processor->thisState);
  Container<Logger>::get()->log(buffer);

  Container<Blink>::get()->dropBlinkTask();
}