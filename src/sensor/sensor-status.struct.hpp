#ifndef SENSOR_STATUS_STRUCT_HPP
#define SENSOR_STATUS_STRUCT_HPP

struct SensorStatus
{
  long timestamp = 0;
  float shuntVoltage = 0;
  float batteryVoltage = 0;
  float current = 0;
  float power = 0;
};

#endif