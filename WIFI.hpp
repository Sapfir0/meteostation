#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

class WIFI
{
private:
    //пока не решил сюда добавлять методы
public:
    WIFI(/* args */);
    ~WIFI();
};

WiFiClient client;

inline void connectToServer(String CityID, String APIKEY) {
  if (client.connect("api.openweathermap.org", 80)) {  //starts client connection, checks for connection
          client.println("GET /data/2.5/weather?id="+CityID+"&units=metric&APPID="+APIKEY);
          client.println("Host: api.openweathermap.org");
          client.println("User-Agent: ArduinoWiFi/1.1");
          client.println("Connection: close");
          client.println();
  } 
  else {
         Serial.println("connection failed");        //error message if no client connect
         Serial.println();
       }
}
