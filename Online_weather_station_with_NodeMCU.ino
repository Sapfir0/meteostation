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
  
  lcd.clear(); //rewrite
  lcd.print("   Connected!");
  Serial.println("Connected");
  delay(1000);
}

void loop() {
  static int counter = 60;
  static int zaderjka=5000;
  static unsigned long time1; //пусть пока полежит в глобале
  static unsigned long time2; //пусть пока полежит в глобале
  static unsigned long time3; //пусть пока полежит в глобале


  if (counter == 60) {  // Get new data every n minutes
    counter = 0;
    led.displayGettingData();
    delay(1000);
    esp8266Module.getWeatherData();
  } else {
    counter++;


    led.displayWeather(esp8266Module.getWeatherLocation(),
                       esp8266Module.getWeatherDescription(),
                       esp8266Module.getCountry());
    delay(zaderjka);    
    led.displayConditions(esp8266Module.getTemperature(),
                          esp8266Module.getHumidity(),
                          esp8266Module.getPressure());
delay(zaderjka);
    // float tempT = gradusnik.getTemperature(); //НЕ СТАТИК
    // float tempH = gradusnik.getHumidity(); //ВСЕ ЕЩЕ НЕТ


    //if(millis() - time1 > zaderjka) {
     // time1 = millis();
      //if ( tempT != gradusnik.getTemperature() or tempH != gradusnik.getHumidity()) {
        led.displayDHT(gradusnik.getTemperature(), 
                       gradusnik.getHumidity(),
                       gradusnik.getIluminating());
      //  }
   // }
   delay(zaderjka);
  }


}

