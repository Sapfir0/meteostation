#include "DHT.hpp"
#include "LCD.hpp"
#include "RGB.hpp"

LCD led;
WIFI esp8266Module;
Gradusnik gradusnik;
RGB diod;

void setup() {
  gradusnik.start();
  led.startLCD();
  esp8266Module.startWifiModule();
  Serial.begin(115200);
  Serial.println("Connecting");

  lcd.clear(); // rewrite
  lcd.print("   Connected!");
  Serial.println("Connected");
  delay(1000);
}

void loop() {
  static int counter = 60;
  static int zaderjka = 5000;

  if (counter == 60) { // Get new data every n minutes
    counter = 0;
    led.displayGettingData();
    delay(1000);
    esp8266Module.getWeatherData();
  }
  else  {
    counter++;
    changeValuesOnLCD();
    delay(1000);
  }
}

void changeValuesOnLCD() {

  led.displayWeather(esp8266Module.getWeatherLocation(),
                     esp8266Module.getWeatherDescription(),
                     esp8266Module.getCountry());
  delay(5000);
  led.displayConditions(esp8266Module.getTemperature(),
                        esp8266Module.getHumidity(),
                        esp8266Module.toMmRtSt(esp8266Module.getPressure()));
  //diod.setColor( esp8266Module.getWeatherID() ); //зависает на вызове
  delay(5000);

  led.displayDHT(gradusnik.getTemperature(), gradusnik.getHumidity(),
                 gradusnik.getIluminating());

  delay(5000); //эффект обновления экрана устранен из-за неработающего фоторезистора

  /*цель
  сделать чтобы как минимум последнее было изменяемым во время работы
  то есть, когда мы отрисовываем этот блок, и поменялось значение, хочу
  чтобы менялось оно не к следующей отрисовке, а моментально */
}
