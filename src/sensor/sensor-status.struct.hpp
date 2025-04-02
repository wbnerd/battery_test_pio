#ifndef SENSOR_STATUS_STRUCT_HPP
#define SENSOR_STATUS_STRUCT_HPP

struct SensorStatus
{
  float shuntVoltage = 0; // IN solid volts
  float batteryVoltage = 0; // IN solid volts
  float current = 0; // IN mA
  float power = 0;
};

#endif