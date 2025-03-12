#ifndef blink_task_struct_header
#define blink_task_struct_header

#include <Arduino.h>

struct BlinkTask
{
  uint8_t times; // количество миганий в таске, 0 - бесконечно
  unsigned long length; // длительность включения светодиода
  unsigned long delay; // длительность выключения светодиода
  bool isToLoop; // зацикленная таска, будет повторяться бесконечно
  unsigned long loopPause; // задержка перед повторением таска

  BlinkTask(uint8_t times, unsigned long length, unsigned long delay, bool isToLoop, unsigned long loopPause) {
    this->times = times;
    this->length = length;
    this->delay = delay;
    this->isToLoop = isToLoop;
    this->loopPause = loopPause;
  }
};

#endif