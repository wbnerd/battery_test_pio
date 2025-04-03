#include "sensor.class.hpp"
#include <GyverINA.h>
#include "constants.hpp"
#include "di/container.class.hpp"
#include "logs/logger.hpp"
#include "sensor-status.struct.hpp"

void Sensor::readSensor(SensorStatus& status) {
  status.current = abs(currentSensor.getCurrent()) * 1000;
  status.batteryVoltage = abs(currentSensor.getVoltage());
  status.power = abs(currentSensor.getPower());
  status.shuntVoltage = abs(currentSensor.getShuntVoltage());
}

bool Sensor::testConnection() {
  Wire.beginTransmission(INA_ADDRESS);  // Начинаем передачу
  return (bool)!Wire.endTransmission();  // Сразу заканчиваем, инвертируем результат
}

Sensor::Sensor() {
  char buffer[32];

  currentSensor.begin(SDA_PIN, SCL_PIN);

  Logger::log(F("Sensor connected!"));

  sprintf(buffer, "Calibration value: %d", currentSensor.getCalibration());
  Logger::log(buffer);

  currentSensor.adjCalibration(calibrI); //Калибровочное значение тока

  // Для повышения помехозащищенности INA226 имеет возможность настроить время выборки напряжения и тока
  // INA226 будет захватывать "кусок" сигнала выбранной продолжительности, что повысит точность на шумном сигнале
  // По умолчанию выборка занимает 1100 мкс, но может быть изменена методом .setSampleTime(канал, время);
  // Варианты времени выборки см. в таблице (файл INA226.h)
  currentSensor.setSampleTime(INA226_VBUS, INA226_CONV_8244US);   // Повысим время выборки напряжения в 8 раз
  currentSensor.setSampleTime(INA226_VSHUNT, INA226_CONV_8244US); // Повысим время выборки тока в 8 раз

  // Так же имеется возможность использовать встроенное усреднение выборок
  // Усреднение применяется и для напряжения и для тока и пропорционально увеличивает время оцифровки
  // Рекомендуется на шумной нагрузке, устанавливается методом .setAveraging(кол-во усреднений) (см. таблицу в INA226.h)
  currentSensor.setAveraging(INA226_AVG_X4); // Включим встроенное 4х кратное усреднение, по умолчанию усреднения нет
}

Sensor::~Sensor() {
    // Destructor implementation
}