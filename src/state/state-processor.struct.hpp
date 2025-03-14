#ifndef state_processor_struct_header
#define state_processor_struct_header

#include <Arduino.h>
#include "state-step.enum.hpp"
#include "../blink/blink-task.struct.hpp"

struct StateProcessor {
  StateStep thisState;
  StateStep fromState;
  BlinkTask blinkTask;
  StateStep (*enter)(StateProcessor* processor);
  StateStep (*exit)(StateProcessor* processor);
  StateStep (*iterate)(StateProcessor* processor);

  StateProcessor(
    StateStep thisState,
    StateStep fromState,
    BlinkTask blinkTask,
    StateStep (*enter)(StateProcessor* processor),
    StateStep (*exit)(StateProcessor* processor),
    StateStep (*iterate)(StateProcessor* processor)
  ) : thisState(thisState), fromState(fromState), blinkTask(blinkTask), enter(enter), exit(exit), iterate(iterate) {}
};

#endif
