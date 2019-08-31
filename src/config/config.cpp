#include "config.h"

#include <DHT.h>

const String CityID = "472757"; // Your City ID
const String openweathermapServer = "http://api.openweathermap.org/data/2.5/weather";
const String APIKEY = "9881fdc10d1d14339a3a6514d415efa4"; //api openweathermap
const String ssid = "Home mommy"; // SSID of local network
const String password = "sapfir1997";   // Password on network

// pins
const uint8_t DHTPIN = D4;
const uint8_t DHTTYPE = DHT11;

const uint8_t analogPin = A0;
const uint8_t LedLight = D6;

const String meteoserver = "http://meteo-server.herokuapp.com";
const String routing = "/meteostationData";
const int meteostationId = 1;
