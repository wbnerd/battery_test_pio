#ifndef state_processor_abstract_header
#define state_processor_abstract_header

#include "state-step.enum.hpp"
#include "state-processor.struct.hpp"

void abstractStateEnter(StateProcessor* processor);
void abstractStateExit(StateProcessor* processor);

#endif