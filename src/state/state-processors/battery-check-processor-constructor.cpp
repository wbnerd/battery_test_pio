#include <blink/blink.class.hpp>
#include "state-processors.hpp"
#include <constants.hpp>
#include <GyverOLED.h>

GyverOLED<SSD1306_128x64, OLED_NO_BUFFER> oled;

void batteryCheckEnter(StateProcessor* processor, StateStep from) {
  Serial.begin(SERIAL_SPEED);
  Serial.println();
  Serial.println("Battery check initiated");

  blinker.appendBlinkTask(processor->blinkTask);

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


    if (I < 0.5) { // проверка, есть ли потребление больше 0.5 мА
      oled.clear();
      oled.setScale(2);
      oled.setCursor(0, 1);
      oled.print("Подключите");
      oled.setCursor(0, 3);
      oled.print("нагрузочный");
      oled.setCursor(0, 5);
      oled.print("резистор");
      continue; // возвращаемся к началу цикла
    }

    startMillis = millis(); // Сброс времени начала отсчёта
    metering(); // Первое измерение
    // Определение типа батарейки для установки напряжения окончания теста
    if (U > 2) Ustop = 2; // Батарейки 3V (CR 2032, CR123A и пр.)
    if (U > 3.5) Ustop = 2.5; // Литиевые аккумуляторы 3.7V
    if (U > 5.4) Ustop = 5.4; // "Крона" 9V
    if (U > 10.5) Ustop = 10.5; // Свинцовые батареи 12V


    if (U > 15) {
      oled.clear();
      oled.setScale(2);
      oled.setCursor(0, 1);
      oled.print("Напряжение");
      oled.setCursor(0, 3);
      oled.print("выше");
      oled.setCursor(0, 5);
      oled.print("15 вольт");
      while (true); // Бесконечный цикл для остановки
    }

    delay(500); // Задержка между измерениями (нужна в том числе для того, чтобы не падал ESP8266)
    read_ina(); // Чтение данных из INA
    if (U >= 0.5) break; // ждём, пока появится напряжение больше 0.5 В
  }

}

void batteryCheckExit(StateProcessor* processor) {
  Serial.println("batteryCheck exit");
}

StateProcessor* BatteryCheckStateProcessor() {
  StateProcessor* processor = new StateProcessor{
    BATTERY_CHECK,
    {BATTERY_CHECK, BLINK_LENGTH, BLINK_DELAY, true, 1000},
    batteryCheckEnter,
    batteryCheckExit
  };

  return processor;
}