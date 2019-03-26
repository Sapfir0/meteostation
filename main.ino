#include "DHT.hpp"
#include "LCD.hpp"
#include "RGB.hpp"
//#include "Snake.hpp"
#include <LiquidCrystalRus.h>  //attention! only for arduino

LCD led;
WIFI esp8266Module;
Gradusnik gradusnik;
RGB diod;

void setup() {
  noInterrupts();  // no concurency

  gradusnik.start();
  led.startLCD();
  esp8266Module.startWifiModule();
  diod.startRgb();
  Serial.begin(115200);
  Serial.println("Connecting");

  lcd.clear();  // rewrite
  lcd.print("   Connected!");
  Serial.println("Connected");

  delay(1000);

  interrupts();  // YES concurency
}

int TaskTimer1 = 0, TaskTimer2 = 0, TaskTimer3 = 0;

bool TaskFlag1 = false, TaskFlag2 = false, TaskFlag3 = false;

#define timeForLCD 5000

void loop() {
  static int counter = 60;
  static int lag = 5000;

  if (counter == 60) {  // Get new data every n minutes
    counter = 0;
    led.displayGettingData();
    delay(1000);
    esp8266Module.getWeatherData();
  } else {
    counter++;
    // changeValuesOnLCD(lag);  //обычный режим
    static int tackter = 0;

    // 3 вывода с леда должны выводиться каждые 5 секунд, пока идет 5 секунд
    // паузы, можно выполянть другие процессы
    if (TaskFlag1) {
      TaskFlag1 = false;
      led.displayWeather(
          esp8266Module.getWeatherLocation(),
          esp8266Module.getWeatherDescription(),
          // esp8266Module.getRussianDescription(esp8266Module.getWeatherID() ),
          esp8266Module.getCountry());
    }
    if (TaskFlag2) {
      TaskFlag2 = false;
      led.displayConditions(
          esp8266Module.getTemperature(), esp8266Module.getHumidity(),
          esp8266Module.toMmRtSt(
              esp8266Module.getPressure()));  // 765мм рт ст - норма
    }
    if (TaskFlag3) {
      TaskFlag3 = false;
      led.displayDHT(
          gradusnik.getTemperature(),
          gradusnik
              .getHumidity(),  //зимой 30-45%, летом 30-60% нормальная влажность
          gradusnik.getIluminating());
    }

    //такие как дать прогноз
    int a = diod.getHorecast(esp8266Module.getTemperature(),
                             esp8266Module.getHumidity(),
                             esp8266Module.getPressure());
    diod.setColorByRating(a);
    //и эффект
    diod.fading();
    delay(1000);
  }
}

void changeValuesOnLCD(int lag) {
  /*цель
  сделать чтобы как минимум последнее было изменяемым во время работы
  то есть, когда мы отрисовываем этот блок, и поменялось значение, хочу
  чтобы менялось оно не к следующей отрисовке, а моментально */
}

ISR(TIMER2_COMPA_vect) {
  TaskTimer1++;
  TaskTimer2++;
  TaskTimer3++;

  if (TaskTimer1 > timeForLCD - 1) {
    TaskTimer1 = 0;
    TaskFlag1 = true;
  }
  if (TaskTimer2 > timeForLCD - 1) {  // scroll message (250mS)
    TaskTimer2 = 0;
    TaskFlag2 = true;
  }
  if (TaskTimer3 > timeForLCD - 1) {  // bargraph (100mS)
    TaskTimer3 = 0;
    TaskFlag3 = true;
  }
}
