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

int  counter = 60;                                      

String weatherDescription ="";
String weatherLocation = "";
String Country;
float Temperature;
float Humidity;
float Pressure;

LiquidCrystal_I2C lcd(0x27, 16, 2);    // Address of your i2c LCD back pack should be updated.

void startLCD() {
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
  lcd.print("   Connecting");  
}

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
  startLCD();
  startWifiModule();

  Serial.begin(115200);
  Serial.println("Connecting");
  lcd.clear();
  lcd.print("   Connected!");
  Serial.println("Connected");
  delay(1000);
}

void loop() {
    if(counter == 60)                                 //Get new data every 10 minutes
    {
      counter = 0;
      displayGettingData();
      delay(1000);
      getWeatherData();
    }else
    {
      counter++;
      displayWeather(weatherLocation,weatherDescription);
      delay(5000);
      displayConditions(Temperature,Humidity,Pressure);
      delay(5000);
    }
}

void displayWeather(String location,String description)
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(location);
  lcd.print(", ");
  lcd.print(Country);
  lcd.setCursor(0,1);
  lcd.print(description);
}




void getWeatherData()                                //client function to send/receive GET request data.
{
  connectToServer(CityID, APIKEY);

  while(client.connected() && !client.available()) 
  delay(1);                                          //waits for data
  while (client.connected() || client.available())  {
      //connected or data available
         char c = client.read();                     //gets byte from ethernet buffer
         result = result+c;
  }

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



void displayConditions(float Temperature,float Humidity, float Pressure)
{
 lcd.clear();                            //Printing Temperature
 lcd.print("T:"); 
 lcd.print(Temperature,1);
 lcd.print((char)223);
 lcd.print("C "); 
                                         
 lcd.print(" H:");                       //Printing Humidity
 lcd.print(Humidity,0);
 lcd.print(" %"); 
 
 lcd.setCursor(0,1);                     //Printing Pressure
 lcd.print("P: ");
 lcd.print(Pressure,1);
 lcd.print(" hPa");
}

void displayGettingData()
{
  lcd.clear();
  lcd.print("Getting data");
}
