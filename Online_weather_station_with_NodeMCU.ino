#include "WIFI.hpp"
#include "LCD.hpp"
#include "DHT.hpp"

                                     // Пин к которому подключен датчик температуры

const char* ssid     = "WiFi-DOM.ru-1520";                 // SSID of local network
const char* password =  "sapfir1997";                    // Password on network

                                 
LCD led;
WIFI esp8266Module;
Gradusnik gradusnik;

void setup() {
  gradusnik.start();
  led.startLCD();
  esp8266Module.startWifiModule(ssid, password);
  Serial.begin(115200);
  Serial.println("Connecting");
  lcd.clear();
  lcd.print("   Connected!");
  Serial.println("Connected");
  delay(1000);
}

void loop() {
   static int  counter = 60;  
    if(counter == 60)   {//Get new data every 10 minutes  
      counter = 0;
      led.displayGettingData();
      delay(1000);
      esp8266Module.getWeatherData();
    }
    else   {
      counter++;
      led.displayWeather(esp8266Module.getWeatherLocation(),esp8266Module.getWeatherDescription(), esp8266Module.getCountry());
      delay(5000);
      led.displayConditions( esp8266Module.getTemperature(), esp8266Module.getHumidity(), esp8266Module.getPressure() );
      delay(5000);
      led.displayDHT( gradusnik.getTemperature(), gradusnik.getHumidity() );
      delay(5000);


    }

}
