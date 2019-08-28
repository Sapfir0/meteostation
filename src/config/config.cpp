#include "config.h"

#include <DHT.h>

const String CityID = "472757"; // Your City ID
const String APIKEY = "9881fdc10d1d14339a3a6514d415efa4"; //api openweathermap
const String ssid = "Home mommy"; // SSID of local network
const String password = "sapfir1997";   // Password on network

// pins
const uint8_t DHTPIN = D4;
const uint8_t DHTTYPE = DHT11;

const uint8_t analogPin = A0;
const uint8_t LedLight = D6;
const uint8_t rgbPins[3] = {D5, D8, D7};

const String ourServer = "meteo-server.herokuapp.com";
const String routing = "/meteostationData";
const int meteostationId = 1;