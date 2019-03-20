#include "DHT.hpp"
#include "LCD.hpp"

LCD led;
WIFI esp8266Module;
Gradusnik gradusnik;

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
  delay(5000);

  static int counter = 0;
  static int t, h, i;
  t = gradusnik.getTemperature();
  h = gradusnik.getHumidity();

  i = gradusnik.getIluminating();
  while (counter < 2)
  {
    if (t != gradusnik.getTemperature() or h != gradusnik.getHumidity() or i != gradusnik.getIluminating())
    {
      led.displayDHT(gradusnik.getTemperature(), gradusnik.getHumidity(),
                     gradusnik.getIluminating());
    } ///не особо понял как робит фоторезистор, он какую-то муть показывает
    counter++;
    delay(5000); //эффект обновления экрана устранен из-за неработающего фоторезистора
  }
  counter = 0;

  /*цель
  сделать чтобы как минимум последнее было изменяемым во время работы
  то есть, когда мы отрисовываем этот блок, и поменялось значение, хочу
  чтобы менялось оно не к следующей отрисовке, а моментально */
}
