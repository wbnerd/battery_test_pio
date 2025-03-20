#include <blink/blink.class.hpp>
#include "state-processors.hpp"
#include <constants.hpp>
#include <GyverINA.h>
#include <GyverOLED.h>

GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;
INA226 currentSensor; // Запуск INA

void batteryRequestEnter(StateProcessor* processor, StateStep from) {
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

    delay(500); // Задержка между измерениями (нужна в том числе для того, чтобы не падал ESP8266)
    read_ina(); // Чтение данных из INA
    if (U >= 0.5) break; // ждём, пока появится напряжение больше 0.5 В
  }

}


StateProcessor* BatteryRequestStateProcessor() {
  StateProcessor* processor = new StateProcessor{
    BATTERY_REQUEST,
    {BATTERY_REQUEST, BLINK_LENGTH, BLINK_DELAY, true, 1000},
    batteryRequestEnter,
    batteryRequestExit
  };

  return processor;
}