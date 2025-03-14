#include <blink/blink.class.hpp>
#include "state-processors.hpp"
#include <constants.hpp>

void testEnter(StateProcessor* processor, StateStep from) {
  Serial.println();
  Serial.println("Test initiated");

  blinker.appendBlinkTask(processor->blinkTask);
}

void testExit(StateProcessor* processor) {
  Serial.println("Test exit");
}


void datacom() //вывод строки данных в COM-порт
{
  MillisCom = millis() - startMillis + serialmills; //Устанавливаем время следующего вывода в порт

  // Подготовка экрана, вывод обозначений параметров мелким шрифтом
  oled.clear();
  oled.setScale(1);
  oled.setCursorXY(50, 31);
  oled.print("V");
  oled.setCursorXY(40, 55);
  oled.print("mA");
  oled.setCursorXY(111, 31);
  oled.print("mWh");
  oled.setCursorXY(111, 55);
  oled.print("mAh");
  oled.setScale(2); // масштаб текста (1..4)

  Serial.print(hours);
  Serial.print(":");
  if (minutes < 10) Serial.print("0");
  Serial.print(minutes);
  Serial.print(":");
  if (seconds < 10) Serial.print("0");
  Serial.print(seconds);
  Serial.print(" ");
  Serial.print(U, 4); //напряжение, 4 знака после запятой
  Serial.print(" ");
  Serial.print(I, 2); //ток, 2 знака после запятой
  Serial.print(" ");
  Serial.print(mwh, 1); //энергия, 1 знак после запятой
  Serial.print(" ");
  Serial.println(mah, 1); //ёмкость, 1 знак после запятой
  }


  void metering() //измерение
  {
    read_ina(); //Чтение данных из INA
    mah += (I/7200); //7200 измерений в час
    mwh += (I/7200 * U);

  }

  void read_ina() //Чтение данных из INA
  {
    U = currentSensor.getVoltage();
    U *= calibrU;
    I = currentSensor.getCurrent();
    I *= 1000;
  }

  void timeprint() //Вывод времени
  {
    oled.setCursor(0, 0);

    if (millis() < (startMillis + 36000000000)) //Проверка, не превышен ли лимит 1000 часов
    {
      oled.print(hours);
      oled.print(":");
      if (minutes < 10) oled.print("0");
      oled.print(minutes);
      oled.print(":");
      if (seconds < 10) oled.print("0");
      oled.print(seconds);
    }
    else oled.print(">1000 часов");
  }

  void autonum(float param, int x, int y, int numdigit) //Вывод на экран целого числа с автовставкой пробелов для выравнивания по правому краю
  //x, y - координаты курсора, numdigit - количесто цифр 3, 4 или 5
  //дробное значение автоматически округляется
  {
    oled.setCursorXY(x, y);
    if (numdigit == 5) if (param < 9999.5) oled.print(" ");
    if (numdigit >= 4) if (param < 999.5) oled.print(" ");
    if (param < 99.5) oled.print(" ");
    if (param < 9.5) oled.print(" ");
    if (param < 99999.5) oled.print(param, 0);
    else oled.print(">100K");
    if (numdigit == 4) if (param >= 9999.5) oled.print(" "); //затираем mAh/mWh в режиме измерения если значение больше 9999
  }




void iterate() {
  //Serial.print (U, 9); //Для отладки - вывод значений измерений и подсчтов в COM-порт с 9 знаками после запятой
  //Serial.print (" V ");
  //Serial.print (I, 9);
  //Serial.print (" mA ");
  //Serial.print (mah, 9);
  //Serial.print (" mAh ");
  //Serial.print (mwh, 9);
  //Serial.println(" mwh");

  if (millis() >= (startMillis + MillisTake)) { // Пора ли делать измерение?
    MillisTake = (millis() - startMillis + 500); // Устанавливаем время следующего измерения
    metering(); // Измерение

    // рассчитываем и выводим время
    seconds = (millis() - startMillis) / 1000;
    minutes = seconds / 60;
    hours = minutes / 60;
    seconds %= 60;
    minutes %= 60;
    timeprint(); // вывод времени на экран

    // Вывод значений на экран
    oled.setCursor(0, 3);
    if (U >= 10) oled.print(U, 1); // Если напряжение больше 10 В оставляем только 1 знак после запятой
    else oled.print(U, 2);
    oled.setCursor(0, 6);
    autonum(I, 0, 48, 3);
    autonum(mwh, 60, 24, 4);
    autonum(mah, 60, 48, 4);

    if (millis() >= (startMillis + MillisCom)) datacom(); // Вывод в COM-порт если настало время

    if (millis() > (startMillis + 5000) && Ustop > U) { // Если прошло более 5 секунд с начала, проверяем не закончился ли тест
      // Финальный экран
      datacom(); // Вывод в COM-порт последнего значения
      Serial.println("END");

      while (true) { // Вывод картинки с дохлой батарейкой
        // oled.drawBitmap(0, 0, dead_128x64, 128, 64, BITMAP_NORMAL, BUF_ADD);
        delay(2000);
        oled.clear();
        oled.setScale(2);
        timeprint(); // вывод времени
        oled.setScale(3);
        autonum(mwh, 0, 17, 5);
        autonum(mah, 0, 40, 5);
        oled.setScale(2);
        oled.setCursorXY(92, 24);
        oled.print("mWh");
        oled.setCursorXY(92, 47);
        oled.print("mAh");
        delay(3000);

        if (animacount == 0) {
          oled.setContrast(1); // уменьшаем яркость, чтобы меньше выгорал экран
        } else {
          animacount--;
        }
      }
    }
  }
}

StateProcessor* TestStateProcessor() {
  StateProcessor* processor = new StateProcessor{
    TEST,
    {TEST, BLINK_LENGTH, BLINK_DELAY, true, 1000},
    testEnter,
    testExit
  };

  return processor;
}
