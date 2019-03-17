// Robo India Tutorials
// Hardware: NodeMCU
// simple Code for reading information from openweathermap.org 

#include <ESP8266WiFi.h>
#include <LiquidCrystal_I2C.h>
#include <ArduinoJson.h>
#include <Wire.h>

#include "WIFI.hpp"
#include "LCD.hpp"

const char* ssid     = "WiFi-DOM.ru-1520";                 // SSID of local network
const char* password =  "sapfir1997";                    // Password on network
String APIKEY = "9881fdc10d1d14339a3a6514d415efa4";                                 
String CityID = "472757";                                 //Your City ID


char servername[]="api.openweathermap.org";              // remote server we will connect to
String result;
    String weatherDescription ="";
    String weatherLocation = "";
    String Country;
    float Temperature;
    float Humidity;
    float Pressure;
int  counter = 60;                                      

LCD led;
WIFI esp8266Module;

void startWifiModule() {
    WiFi.begin(ssid, password);
    int cursorPosition=0;

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        lcd.setCursor(cursorPosition,2); 
        lcd.print(".");
        cursorPosition++;
    }
}

void setup() {

  led.startLCD();
  startWifiModule();

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
      getWeatherData();
    }
    else   {
      counter++;
      led.displayWeather(weatherLocation,weatherDescription, Country);
      delay(5000);
      led.displayConditions(Temperature,Humidity,Pressure);
      delay(5000);
    }
}


void getWeatherData()                                //client function to send/receive GET request data.
{
  esp8266Module.connectToServer(CityID, APIKEY);

 result = esp8266Module.queryToServer(result);

client.stop();                                      //stop client
result.replace('[', ' ');
result.replace(']', ' ');
Serial.println(result);
char jsonArray [result.length()+1];
result.toCharArray(jsonArray,sizeof(jsonArray));
jsonArray[result.length() + 1] = '\0';
StaticJsonBuffer<1024> json_buf;
JsonObject &root = json_buf.parseObject(jsonArray);

if (!root.success())  {
    Serial.println("parseObject() failed");
}

String location = root["name"];
String country = root["sys"]["country"];
float temperature = root["main"]["temp"];
float humidity = root["main"]["humidity"];
String weather = root["weather"]["main"];
String description = root["weather"]["description"];
float pressure = root["main"]["pressure"];

weatherDescription = description;
weatherLocation = location;
Country = country;
Temperature = temperature;
Humidity = humidity;
Pressure = pressure;

}
