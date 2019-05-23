#pragma once

#include "config.hpp"
#include <ArduinoJson.h>
#include <ESP8266WiFi.h> //default library for nodemcu, commit this if u use arduino
#include "DHT.hpp"
#include <ctime>

    extern const String CityID; // Your City ID
    extern const String APIKEY;
    extern const char *_ssid; // SSID of local network
    extern const char *password;   // Password on network

    extern const String apiKey;  // replace with your channel’s thingspeak API key,
    extern const char* server;
    extern const char *ourServer;

    class WIFI
    {
    private:
      String result;

      //мм свойства
      String weatherDescription = "";
      String weatherLocation = "";
      String Country;
      float Temperature;
      float Humidity;
      float Pressure;
      int weatherID;
      int windSpeed;

    public:
      void connectToServer(String CityID, String APIKEY);
      String getResponseFromServer(String result);
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
      int getWindSpeed();
      void setWeatherDescription(String weatherDescription);
      void setWeatherLocation(String weatherLocation);
      void setCountry(String country);
      void setTemperature(float temperature);
      void setHumidity(float humidity);
      void setPressure(float pressure);
      void setWeatherID(int weatherID);
      void setWindSpeed(int windSpeed);

      const char *getSSID();
      void setSSID(const char *ssid);

      String getRussianDescription(int weatherID);
      String getBetterRussianDescription(int weatherID);

};

WiFiClient client;

void WIFI::postToOurServer() {
  Gradusnik grad;
  // if (!client.connect(server, 80)) {
  //   Serial.println("connection failed"); 
  //   return -1;
  // }

  std::time_t result = std::time(nullptr);

  DynamicJsonDocument request(1024);
  request["TempInHome"] = grad.getTemperature();
  request["HumInHome"] = grad.getHumidity();
  request["Temperature"] = getTemperature();
  request["Pressure"] = getPressure();
  request["WeatherDescription"] = getBetterRussianDescription(getWeatherID());
  request["CURRENTTIMESTAMP"] = std::asctime(std::localtime(&result))
  serializeJson(request, Serial)
  Serial.println("до этого должен быть джсон");
  client.println(F("HTTP/1.0 200 OK"));
  client.println(F("Content-Type: application/json"));
  client.println(F("Connection: close"));
  client.print(F("Content-Length: ")); //возможно, нужно кидать длину джсона сначала, проверить это
  client.println(measureJsonPretty(doc));
  client.println();
}

void WIFI::parsingJSON(String json)  { //переход на новую версию

  json.replace('[', ' ');
  json.replace(']', ' ');
  Serial.println(json);
  // char jsonArray[json.length() + 1];
  // json.toCharArray(jsonArray, sizeof(jsonArray));
  // jsonArray[json.length() + 1] = '\0';
  //StaticJsonBuffer<1024> json_buf;
  //JsonObject root = json_buf.parseObject(jsonArray); //уже не ставится амперсант
  JsonObject root = json.as<JsonObject>();
  Serial.println(root)
  setWeatherLocation(root["name"]);
  setCountry(root["sys"]["country"]);
  setTemperature(root["main"]["temp"]);
  setHumidity(root["main"]["humidity"]);
  setPressure(root["main"]["pressure"]);
  setWeatherID(root["weather"]["id"]);
  setWindSpeed(root["wind"]["speed"]);

  setWeatherDescription(root["weather"]["0"]["description"]);
  //setWeatherID(root["weather"]["0"]["id"]); //если погода в городе разная, то станций будет много, и нужно получать хотя бы с одной
  setWeatherID(root["weather"]["id"]);
  Serial.println(getWeatherID());
}


void WIFI::startWifiModule()
{
  WiFi.begin(_ssid, password);

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

String WIFI::getResponseFromServer(String result)
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
  result = getResponseFromServer(result);
  parsingJSON(result);
}

float WIFI::toMmRtSt(float GectoPaskal) {
  float res = 0;
  res = GectoPaskal * 100 / 133;
  return res;
}


String WIFI::getBetterRussianDescription(int weatherID) {
  String temp = getRussianDescription(weatherID);
  temp.trim();
  //проходим по строке и убираем двойной пробел
  for(int i = 0; i < temp.length()-2; i++)  {
    if (temp[i] == ' ' and temp[i+1] == ' ') {//почему не isSpace
      temp.remove(i,1); //удалить пробел
    }
  }
//   if (temp.length() > 16) { //если строка длиннее 16 символов
//  //то делаем перенос следующих символов на следующую строчку   
//   }
  return temp;
}

String WIFI::getRussianDescription(int weatherID) {
  //map<char, String> mapa;
  
  String thunderstorm = " гроза " ;
  String with = " c " ;
  String with2 =  " co " ;
  String drizzle =  " морось " ;
  String weakIy =  " слабый " ;
  String weakAya =  " слабая " ;
  String heavyIy =  " сильный " ;
  String heavyAya =  " сильная " ;
  String heavyIm =  " сильным " ;
  String grad =  " град " ;
  String gololed =  " гололедица " ;
  String moros =  " моросящий " ;
  String moderate =  " умеренный " ;
  String sneg =  " снег " ;
  String snegOm =  " снегом " ;

  String rainEm =  " дождем " ;
  String rainB =  " дождь " ;
  String heavyRainB =  " ливень " ;
  String fog =  " туман " ;
  String snow =  " снегопад " ;
  String mestami =  " местами " ;
  String freezing =  " замерзающий " ;
  String shower =  " ливневый " ;
  String small =  " небольшая " ;
  String sep =  ", ";

  String slabo =  " слабо " ;
  String andW =  " и " ;
  String from =  " из " ;
  String smoke =  " дымка " ;
  String mist =   " мгла " ;
  String sandStorm =  " песчаная буря " ;
  String dense =   " густой " ;
  String sandy =   " песочно " ;
  String dusty =   " пыльно " ;
  String OMG =  " ВУЛКАНИЧЕСКИЙ ПЕПЕЛ ГОСПОДИ МЫ ВСЕ УМРЕМ " ;
  String squall =  " шквал " ;
  String tornado =   " торнадо " ;
  String clearSky =   " ясно  " ;
  String lowCloudy =   " немного облачно " ;
  String cloudy =   " облачно " ;
  String cloudyWithClarifications =   " облачно с прояснениями " ;
  String murky =  " пасмурно " ;

    switch (weatherID) {
      case 200:        return thunderstorm + with2 + weakIy + rainEm;  //гроза со слабым доджем
      case 201:        return thunderstorm + with + rainEm;  //гроза с дождем
      case 202:        return thunderstorm + with + heavyIm + rainEm;
      case 210:        return weakAya + thunderstorm;
      case 211:        return thunderstorm;
      case 212:        return heavyAya + thunderstorm;
      case 221:        return mestami + thunderstorm;
      case 230:        return thunderstorm + sep + weakAya + drizzle;
      case 231:        return thunderstorm + sep + drizzle;
      case 232:        return thunderstorm + sep + heavyAya + drizzle;

      case 300:        return weakAya + drizzle;  //слабая морось
      case 301:        return drizzle;
      case 302:        return heavyAya + drizzle;
      case 310:        return slabo + moros + rainB;
      case 311:        return moros + rainB;
      case 312:        return heavyAya + from + moros;
      case 313:        return rainB + andW + drizzle;
      case 321:        return drizzle;

      case 500:        return weakIy + rainB;  //легкий дождь
      case 501:        return moderate + rainB;
      case 502:        return heavyIy + rainB;  //сильный дождь
      case 503:        return heavyRainB;  //ливень
      case 504:        return heavyIy + heavyRainB;  //экстремальный дождь
      case 511:        return freezing + rainB;  //замерзающий дождь
      case 520:        return moderate + heavyRainB;  //слабый ливень
      case 521:        return heavyRainB;  //ливень
      case 522:        return heavyIy + heavyRainB;  //сильный ливень
      case 531:        return mestami + heavyRainB;  //местами ливень

      case 600:        return weakIy + snow;
      case 601:        return snow;
      case 602:        return heavyIy + snow;
      case 611:        return gololed;
      case 612:        return small + gololed;
      case 613:        return grad;
      case 615:        return weakIy + rainB + with2 + snegOm;
      case 616:        return rainB + with2 + snegOm;
      case 620:        return weakIy + grad;
      case 621:        return shower + snegOm;
      case 622:        return heavyIy + shower + sneg;

      case 701:        return fog;
      case 711:        return smoke;
      case 721:        return mist;
      case 731:        return sandStorm;
      case 741:        return dense + fog;
      case 751:        return sandy;
      case 761:        return dusty;
      case 762:        return OMG;
      case 771:        return squall;
      case 781:        return tornado;

      case 800:        return clearSky;

      case 801:        return lowCloudy;
      case 802:        return mestami + cloudy;
      case 803:        return cloudy;
      case 804:        return murky;
      default:
        return "ERROR";
    }
    return "ERROR X2";
}


const char *WIFI::getSSID() {
  return _ssid;
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
int WIFI::getWeatherID() {
  return weatherID;
}
int WIFI::getWindSpeed() {
  return windSpeed;
}

void WIFI::setSSID(const char *ssid)
{
  _ssid = ssid;
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
void WIFI::setWindSpeed(int windSpeed) {
  this->windSpeed = windSpeed;
}
