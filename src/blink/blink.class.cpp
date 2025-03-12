#include <Arduino.h>
#include <Ticker.h>
#include "blink.class.hpp"

Blink::Blink(uint8_t pin, uint8_t upVal)
{
  pinMode(pin, OUTPUT);
  digitalWrite(pin, !upVal);

  _pin = pin;
  _upVal = upVal;
}

bool Blink::setupBlinkTask(const BlinkTask &task)
{
  if (_isInTask)
  {
    return false;
  }

  _startMillis = millis();
  _isInTask = true;
  _isInTask = true;

  _ticker.attach_ms(_resolution, [this, task]() {
    this->iterate(task);
  });

  return true;
}

void Blink::iterate(const BlinkTask &task)
{
  if (!_isInTask)
  {
    clearOnComplete();
  }

  unsigned long currentMillis = millis();
  unsigned long runTime = currentMillis - _startMillis;
  unsigned long iterationLength = task.length + task.delay;
  unsigned long cycleActive = iterationLength * task.times;
  unsigned long cycleLength = cycleActive + (task.isToLoop ? task.loopPause : 0);
  unsigned long cycleTime = runTime % cycleLength;

  if (cycleTime < cycleActive && cycleTime % iterationLength < task.length && !_isLedUp)
  {
    digitalWrite(_pin, _upVal);
    _isLedUp = true;
  }
  else if (cycleTime < cycleActive && cycleTime % iterationLength >= task.length && _isLedUp)
  {
    digitalWrite(_pin, !_upVal);
    _isLedUp = false;
  }

  if (task.times == 0)
  {
    return;
  }

  if (!task.isToLoop && runTime / iterationLength >= task.times)
  {
    clearOnComplete();
  }
}

void Blink::dropBlinkTask()
{
  clearOnComplete();
}

void Blink::clearOnComplete()
{
  digitalWrite(_pin, !_upVal);
  _isLedUp = false;
  _isInTask = false;
  _ticker.detach();
}

void Blink::appendBlinkTask(const BlinkTask &task)
{
  if (_isInTask)
  {
    dropBlinkTask();
  }

  setupBlinkTask(task);
}