#include "state-processor-abstract.hpp"

void abstractStateEnter(StateStep from) {
  Serial.println("Entering state");
}

void abstractStateExit() {
  Serial.println("Exiting state");
}