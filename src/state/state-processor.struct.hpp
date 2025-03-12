#ifndef state_processor_struct_header
#define state_processor_struct_header

#include <Arduino.h>
#include "state-step.enum.hpp"
#include "../blink/blink-task.struct.hpp"

struct StateProcessor {
  StateStep correspondingStep;
  BlinkTask thisStateBlinkTask;
  void (*enter)(StateProcessor* processor, StateStep from);
  void (*exit)(StateProcessor* processor);
  void (*iterate)(StateProcessor* processor);
  void (*initiate)(StateProcessor* processor);

  StateProcessor(
    StateStep correspondingStep,
    BlinkTask thisStateBlinkTask,
    void (*enter)(
      StateProcessor* processor,
      StateStep from),
    void (*exit)(StateProcessor* processor),
    void (*iterate)(StateProcessor* processor),
    void (*initiate)(StateProcessor* processor)
  ) : correspondingStep(correspondingStep), thisStateBlinkTask(thisStateBlinkTask), enter(enter), exit(exit), iterate(iterate), initiate(initiate) {}
};

#endif
