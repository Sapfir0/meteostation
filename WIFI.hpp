#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

class WIFI
{
private:
    String CityID = "472757"; //Your City ID
    String APIKEY = "9881fdc10d1d14339a3a6514d415efa4";
    //char servername[]="api.openweathermap.org";              // not used now-
    String result;                               

    //мм свойства
    String weatherDescription ="";
    String weatherLocation = "";
    String Country;
    float Temperature;
    float Humidity;
    float Pressure;

public:
    void connectToServer(String CityID, String APIKEY);
    String queryToServer(String result);
    void getWeatherData();
    void startWifiModule(const char* ssid, const char* password);

    String getWeatherDescription();
    String getWeatherLocation();
    String getCountry(); 
    float getTemperature();
    float getHumidity();
    float getPressure();
    void setWeatherDescription(String weatherDescription) ;
    void setWeatherLocation(String weatherLocation) ;
    void setCountry(String country) ;
    void setTemperature(float temperature);
    void setHumidity(float humidity) ;
    void setPressure(float pressure);

};

WiFiClient client;

void WIFI::startWifiModule(const char* ssid, const char* password) {
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connection isnt successful");
//        static int cursorPosition=0; //не особо важный код для точечек на LCD
//        lcd.setCursor(cursorPosition,2); 
//        lcd.print(".");
//        cursorPosition++;
    }
}


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



void WIFI::getWeatherData()                                //client function to send/receive GET request data.
{
  connectToServer(CityID, APIKEY);

  result = queryToServer(result);

client.stop();                                      //stop client
result.replace('[', ' ');
result.replace(']', ' ');
Serial.println(result);
char jsonArray [result.length()+1];
result.toCharArray(jsonArray,sizeof(jsonArray));
jsonArray[result.length() + 1] = '\0';
StaticJsonBuffer<1024> json_buf;
JsonObject &root = json_buf.parseObject(jsonArray);

// if (!root.success())  { //надо бы подумать как вернуть на уровень выше
//     Serial.println("parseObject() failed");
// }

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





    String WIFI::getWeatherDescription() {
      return weatherDescription;
    }
    String WIFI::getWeatherLocation() {
      return weatherLocation;
    }
    String WIFI::getCountry() {
      return Country;
    }
    float WIFI::getTemperature() {
      return Temperature;
    }
    float WIFI::getHumidity() {
      return Humidity;
    }
    float WIFI::getPressure() {
      return Pressure;
    }

    void WIFI::setWeatherDescription(String weatherDescription) {
      this->weatherDescription = weatherDescription;
    }
    void WIFI::setWeatherLocation(String weatherLocation) {
      this->weatherLocation = weatherLocation;
    }
    void WIFI::setCountry(String country) {
      this->Country = country;
    }
    void WIFI::setTemperature(float temperature) {
      this->Temperature = temperature;
    }
    void WIFI::setHumidity(float humidity) {
      this->Humidity = humidity;
    }
    void WIFI::setPressure(float pressure) {
      this->Pressure = pressure;
    }
