#ifndef LOGGER_HEADER_HPP
#define LOGGER_HEADER_HPP

#include <Arduino.h>

class Logger {
  public:
    static void log(const char * text) {
      Serial.println(text);
    }

};

#endif