#include <Arduino.h>
#include "blink/blink.class.hpp"

#define serialmills 5000; //Периодичность вывода в com-порт, мс

void metering();
void datacom();
void autonum(float param, int x, int y, int numdigit);
void timeprint();
void read_ina();

unsigned long startMillis; //Время в момент начала измерения
unsigned long MillisTake; //Время следующего измерения
unsigned long MillisCom; //Время следующего вывода в COM-порт
unsigned long seconds;
unsigned long minutes;
unsigned long hours;
float U; //напряжение в вольтах
float I; //ток в миллиамперах
float mwh = 0; //милливатт-часы
float mah = 0; //миллиампер-часы
float Ustop = 0.9; //Напряжение остановки измерения в вольтах.
int animacount = 20; //количество миганий дохлой батарейкой до снижения яркости

void setup() {
  delay(500); //Задержка для стабилизации питания
}

void loop(void) {
}
