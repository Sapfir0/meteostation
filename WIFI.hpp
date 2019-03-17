#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

class WIFI
{
private:
    //мм свойства

public:
    void connectToServer(String CityID, String APIKEY);
    String queryToServer(String result);

};

WiFiClient client;

void WIFI::connectToServer(String CityID, String APIKEY) {
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


String WIFI::queryToServer(String result) {
      while(client.connected() && !client.available()) 
  delay(1);                                          //waits for data
  while (client.connected() || client.available())  {
      //connected or data available
         char c = client.read();                     //gets byte from ethernet buffer
         result = result+c;
  }
  return result;
}
