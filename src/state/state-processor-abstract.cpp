#include "state-processor-abstract.hpp"
#include "di/container.class.hpp"
#include "logs/logger.hpp"
#include "blink/blink.class.hpp"

void abstractStateEnter(StateProcessor* processor) {
  Container<Blink>::get()->setupBlinkTask(processor->blinkTask);
}

void abstractStateExit(StateProcessor* processor) {
  Container<Blink>::get()->dropBlinkTask();
}