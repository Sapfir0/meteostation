#pragma once

#include <ArduinoJson.h>
#include <ESP8266WiFi.h>

class WIFI
{
private:
  String CityID = "472757"; // Your City ID
  String APIKEY = "9881fdc10d1d14339a3a6514d415efa4";
  String result;

  //мм свойства
  String weatherDescription = "";
  String weatherLocation = "";
  String Country;
  float Temperature;
  float Humidity;
  float Pressure;
  int weatherID;

  const char *ssid = "WiFi-DOM.ru-1520"; // SSID of local network
  const char *password = "sapfir1997";   // Password on network

  //LCD led;
public:
  void connectToServer(String CityID, String APIKEY);
  String queryToServer(String result);
  void getWeatherData();
  void startWifiModule();
  void parsingJSON(String json);
  float toMmRtSt(float GectoPaskal);

  String getWeatherDescription();
  String getWeatherLocation();
  String getCountry();
  float getTemperature();
  float getHumidity();
  float getPressure();
  int getWeatherID();
  void setWeatherDescription(String weatherDescription);
  void setWeatherLocation(String weatherLocation);
  void setCountry(String country);
  void setTemperature(float temperature);
  void setHumidity(float humidity);
  void setPressure(float pressure);
  void setWeatherID(int weatherID);

  const char *getSSID();
  void setSSID(const char *ssid);
};

WiFiClient client;

void WIFI::startWifiModule()
{
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Connection isnt successful");
    //led.loadiiing();  //надо как-то кидать исключение на лсд
  }
}

void WIFI::connectToServer(String CityID, String APIKEY)
{
  if (client.connect("api.openweathermap.org",
                     80))
  { // starts client connection, checks for connection
    client.println("GET /data/2.5/weather?id=" + CityID +
                   "&units=metric&APPID=" + APIKEY);
    client.println("Host: api.openweathermap.org");
    client.println("User-Agent: ArduinoWiFi/1.1");
    client.println("Connection: close");
    client.println();
  }
  else
  {
    Serial.println("connection failed"); // error message if no client connect
    Serial.println();
  }
}

String WIFI::queryToServer(String result)
{
  while (client.connected() && !client.available())
    delay(1); // waits for data
  while (client.connected() || client.available())
  {
    // connected or data available
    char c = client.read(); // gets byte from ethernet buffer
    result = result + c;
  }
  client.stop(); // stop client

  return result;
}

void WIFI::getWeatherData() // client function to send/receive GET request
                            // data.
{
  connectToServer(CityID, APIKEY);
  result = queryToServer(result);
  parsingJSON(result);
}

void WIFI::parsingJSON(String json)
{
  json.replace('[', ' ');
  json.replace(']', ' ');
  Serial.println(json);
  char jsonArray[json.length() + 1];
  json.toCharArray(jsonArray, sizeof(jsonArray));
  jsonArray[json.length() + 1] = '\0';
  StaticJsonBuffer<1024> json_buf;
  JsonObject &root = json_buf.parseObject(jsonArray);

  //String weather = root["weather"]["main"]; //не особо понятно что это

  setWeatherDescription(root["weather"]["description"]);
  setWeatherLocation(root["name"]);
  setCountry(root["sys"]["country"]);
  setTemperature(root["main"]["temp"]);
  setHumidity(root["main"]["humidity"]);
  setPressure(root["main"]["pressure"]);
  setWeatherID(root["weather"]["id"]);
}

float WIFI::toMmRtSt(float GectoPaskal)
{
  float res = 0;
  res = GectoPaskal * 100 / 133;
  return res;
}

const char *WIFI::getSSID() { return ssid; }

String WIFI::getWeatherDescription() { return weatherDescription; }
String WIFI::getWeatherLocation() { return weatherLocation; }
String WIFI::getCountry() { return Country; }
float WIFI::getTemperature() { return Temperature; }
float WIFI::getHumidity() { return Humidity; }
float WIFI::getPressure() { return Pressure; }
int WIFI::getWeatherID() {
  return weatherID;
}

void WIFI::setSSID(const char *ssid)
{
  this->ssid = ssid;
}


void WIFI::setWeatherDescription(String weatherDescription)
{
  this->weatherDescription = weatherDescription;
}
void WIFI::setWeatherLocation(String weatherLocation)
{
  this->weatherLocation = weatherLocation;
}
void WIFI::setCountry(String country)
{
  this->Country = country;
}
void WIFI::setTemperature(float temperature)
{
  this->Temperature = temperature;
}
void WIFI::setHumidity(float humidity)
{
  this->Humidity = humidity;
}
void WIFI::setPressure(float pressure)
{
  this->Pressure = pressure;
}

void WIFI::setWeatherID(int weatherId) {
  this->weatherID = weatherId;
}
