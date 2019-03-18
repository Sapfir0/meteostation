// Robo India Tutorials
// Hardware: NodeMCU
// simple Code for reading information from openweathermap.org 


#include "WIFI.hpp"
#include "LCD.hpp"
#include "DHT.hpp"

//#include "DHT.h"
//#define DHTPIN 6 // номер пина, к которому подсоединен датчик 
//DHT dht(DHTPIN, DHT11); 

const char* ssid     = "WiFi-DOM.ru-1520";                 // SSID of local network
const char* password =  "sapfir1997";                    // Password on network

int  counter = 60;    
                                 
LCD led;
WIFI esp8266Module;

void setup() {

  led.startLCD();
  esp8266Module.startWifiModule(ssid, password);
  //dht.begin();
  Serial.begin(115200);
  Serial.println("Connecting");
  lcd.clear();
  lcd.print("   Connected!");
  Serial.println("Connected");
  delay(1000);
}

void loop() {
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
      Serial.println(esp8266Module.getTemperature());
      delay(5000);
    }
/*
     float h = dht.readHumidity(); 
 //Считываем влажность 
 float t = dht.readTemperature(); 
 // Считываем температуру 
 if (isnan(t) || isnan(h))  {
 Serial.println("Failed to read from DHT");
 } else {
Serial.print("Humidity: ");
Serial.print(h);
Serial.print(" %\t");
Serial.print("Temperature: "); 
Serial.print(t);
Serial.println(" *C");
*/
}
