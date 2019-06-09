#ifndef WIFI_H
#define WIFI_H

#include "../../config/config.hpp"
#include <ArduinoJson.h>
#include <ESP8266WiFi.h> //default library for nodemcu, commit this if u use arduino
#include <ctime>

    extern const String CityID; // Your City ID
    extern const String APIKEY;
    extern const char *_ssid; // SSID of local network
    extern const char *password;   // Password on network
    extern const int id;
    extern const String ourServer;

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
      String icon;
      int windDeg;

    public:
      WIFI();
      void connectToServer(String CityID, String APIKEY);
      void postToOurServer();
      void getWeatherData();
      void startWifiModule();
      void parsingJSON(String json); //мне не нравится, что это здесь
      float toMmRtSt(float GectoPaskal);

      String getWeatherDescription();
      String getWeatherLocation();
      String getCountry();
      float getTemperature();
      float getHumidity();
      float getPressure();
      int getWeatherID();
      int getWindSpeed();
      String getIcon();
      int getWindDeg();
      void setWeatherDescription(String weatherDescription);
      void setWeatherLocation(String weatherLocation);
      void setCountry(String country);
      void setTemperature(float temperature);
      void setHumidity(float humidity);
      void setPressure(float pressure);
      void setWeatherID(int weatherID);
      void setWindSpeed(int windSpeed);
      void setIcon(String icon);
      void setWindDeg(int windDeg);

      const char *getSSID();
      void setSSID(const char *ssid);

};

WiFiClient client;

#include "WIFI.cpp"

#endif // WIFI_H