#pragma once

#include "../config/config.hpp"
#include <ArduinoJson.h>
#include <ESP8266WiFi.h> //default library for nodemcu, commit this if u use arduino
#include "../sensors/DHT.hpp"
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

      void postToOurServer();

};

WiFiClient client;
