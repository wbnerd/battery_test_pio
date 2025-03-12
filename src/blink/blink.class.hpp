#ifndef blink_header
#define blink_header

#include <Arduino.h>
#include <Ticker.h>
#include "blink-task.struct.hpp"

class Blink
{
  public:
  Blink(uint8_t pin, uint8_t upVal);
  bool setupBlinkTask(const BlinkTask &task);
  void appendBlinkTask(const BlinkTask &task);
  void dropBlinkTask();

  private:
    void iterate(const BlinkTask &task);
    void clearOnComplete();
    Ticker _ticker;
    uint8_t _pin; // пин, на котором будет мигать
    uint8_t _upVal; // светодиод включен при HIGH или LOW
    unsigned long _resolution = 50; // разрешение работы таймера в мс
    unsigned long _startMillis; // момет когда началась обработка задачи
    bool _isInTask = false; // исполняется ли сейчас задача
    bool _isLedUp = false; // включен ли светодиод
};

extern Blink blinker;

#endif
