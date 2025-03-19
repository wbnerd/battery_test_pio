#ifndef state_step_enum_header
#define state_step_enum_header
#include <Arduino.h>

enum StateStep: uint8_t {
  START = 0,
  WIFI_SETUP = 2,
  GPIO_SETUP = 3,
  OLED_SETUP = 4,
  INA_SETUP = 5,
  INA_NOT_FOUND = 17,
  BATTERY_CHECK = 6,
  BATTERY_REQUEST = 7,
  BATTERY_ERROR = 8,
  RESISTOR_CHECK = 9,
  RESISTOR_REQUEST = 10,
  RESISTOR_ERROR = 11,
  READY_FOR_TEST = 12,
  TEST = 13,
  TEST_ERROR = 14,
  TEST_END = 15,
  TEST_RESULT = 16,
  STATE_MACHINE_ERROR = 255,
};

#endif