#ifndef state_processor_abstract_header
#define state_processor_abstract_header

#include "state-step.enum.hpp"

void abstractStateEnter(StateStep from);
void abstractStateExit();

#endif