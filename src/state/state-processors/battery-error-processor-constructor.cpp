#include <blink/blink.class.hpp>
#include "state-processors.hpp"
#include <constants.hpp>
#include <GyverINA.h>
#include <GyverOLED.h>

GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;
INA226 currentSensor; // Запуск INA

void batteryErrorEnter(StateProcessor* processor, StateStep from) {
  Serial.begin(SERIAL_SPEED);
  Serial.println();
  Serial.println("Battery error initiated");

  blinker.appendBlinkTask(processor->thisStateBlinkTask);

  while (true) { // Ждём подключения батарейки
    if (millis() > (startMillis + 10000)) break; // заново выводим первую заставку через 10 секунд
    if (millis() > (startMillis + 5000) && millis() < (startMillis + 35300)) { // через 5 секунд меняем заставку на подсказку
      oled.setCursor(0, 3);
      oled.print("Подключите          "); // Пробелы в конце затирают то, что было до этого на экране
      oled.setCursor(0, 4);
      oled.print("нагрузочный резистор");
      oled.setCursor(0, 5);
      oled.print("                    ");
      oled.setCursor(0, 6);
      oled.print("Установите батарейку");
      oled.setCursor(0, 7);
      oled.print("или аккумулятор     ");
    }

    if (millis() > 3600000) { // Требование перезапуска, если прошёл час после включения
      oled.clear();
      oled.setScale(2);
      oled.setCursor(0, 1);
      oled.print("Долгий");
      oled.setCursor(0, 3);
      oled.print("простой.");
      oled.setCursor(0, 5);
      oled.print("Перезапуск");
      while (true); // Бесконечный цикл для перезапуска
    }

    delay(500); // Задержка между измерениями (нужна в том числе для того, чтобы не падал ESP8266)
    read_ina(); // Чтение данных из INA
    if (U >= 0.5) break; // ждём, пока появится напряжение больше 0.5 В
  }

}

void batteryErrorExit(StateProcessor* processor) {
  Serial.println("batteryError exit");
}

StateProcessor* BatteryErrorStateProcessor() {
  StateProcessor* processor = new StateProcessor{
    BATTERY_ERROR,
    {BATTERY_ERROR, BLINK_LENGTH, BLINK_DELAY, true, 1000},
    batteryRequestEnter,
    batteryRequestExit
  };

  return processor;
}