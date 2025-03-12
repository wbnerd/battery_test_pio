#include <blink/blink.class.hpp>
#include "state-processors.hpp"
#include <constants.hpp>
#include <GyverINA.h>
#include <GyverOLED.h>

GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;
INA226 currentSensor; // Запуск INA

void inaSetupEnter(StateProcessor* processor, StateStep from) {
  Serial.println();
  Serial.println("Ina setup");
  blinker.appendBlinkTask(processor->thisStateBlinkTask);

  if (currentSensor.begin(SDA_PIN, SCL_PIN)) {
    Serial.println(F("connected!"));
  } else {
    Serial.println(F("not found!"));
    oled.setCursor(0, 5);
    oled.print("Нет INA226");
  }


  Serial.print(F("INA226..."));
  // Проверяем наличие и инициализируем INA226

  // INA226 имеет возможность встроенной калибровки измерения тока, при помощи специального калибровочного значения
  // После запуска библиотека автоматически рассчитает и запишет калибровочное значение на основе введенных данных
  // Полученное значение можно прочитать, используя метод .getCalibration(); для изменения и/или сохранения в EEPROM
  Serial.print(F("Calibration value: ")); Serial.println(currentSensor.getCalibration());
  // Далее полученное значение можно изменять для подстройки под реальное сопротивление шунта и сохранять в EEPROM
  // Чтобы записать калибровочное значение в INA226 существует метод .setCalibration(value);
  // ina.setCalibration(ina.getCalibration() + 10); // Прочитать-модифицировать-записать калибровочное значение
  // Так же, можно использовать метод .adjCalibration(offset); для подстройки калибровки без непосредственного чтения
  // ina.adjCalibration(10);  // Увеличить калибровочное значение на 10
  // ina.adjCalibration(-110); // Уменьшить калибровочное значение на 110
  // Можно хранить в EEPROM и загружать в INA226 именно смещение калибровки вместо непосредственного значения

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

void inaSetupExit(StateProcessor* processor) {
  Serial.println("INA setup exit");
}

StateProcessor* InaSetupStateProcessor() {
  StateProcessor* processor = new StateProcessor{
    INA_SETUP,
    {INA_SETUP, BLINK_LENGTH, BLINK_DELAY, true, 1000},
    inaSetupEnter,
    inaSetupExit
  };

  return processor;
}