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

  int calibrI = 0; //калибровочное значение тока (отрицательное или положительное)
  float calibrU = 1; //множитель коррекции напряжения при калибровке

  void readSensor(SensorStatus& status);
  static bool testConnection();
};

#endif