#ifndef SENSOR_CLASS_HPP
#define SENSOR_CLASS_HPP
#include <GyverINA.h>
#include "sensor-status.struct.hpp"

class Sensor {
private:
  INA226 currentSensor; // Запуск INA

public:
  Sensor();
  ~Sensor();
  SensorStatus * readSensor();
  static bool testConnection();
};

#endif