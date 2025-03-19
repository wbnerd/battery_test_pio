#define SERIAL_SPEED 74880

#define BLINK_LENGTH 50
#define BLINK_DELAY 300
#define BLINK_PAUSE 1000

//D3
#define BUTTON_PIN 0
//D1
#define RELAY_PIN 5
//D4
#define BLINK_PIN 2
//D5
#define SCL_PIN 14
//D6
#define SDA_PIN 12
//Периодичность вывода в com-порт, мс
#define serialmills 5000;
//Адрес INA226 на шине I2C
#define INA_ADDRESS 0x40


int calibrI = 0; //калибровочное значение тока (отрицательное или положительное)
float calibrU = 1; //множитель коррекции напряжения при калибровке
