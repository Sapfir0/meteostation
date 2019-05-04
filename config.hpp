#pragma once

#ifndef config.hpp
#define config.hpp

#include <Arduino.h>

    const byte rgbPins[3] = {D5, D8, D7};
    const String CityID = "472757"; // Your City ID
    const String APIKEY = "9881fdc10d1d14339a3a6514d415efa4"; //api openweathermap
    const char *_ssid = "WiFi-DOM.ru-1520"; // SSID of local network
    const char *password = "sapfir1997";   // Password on network

    const byte DHTPIN = D4;
    const byte photoresistor = A0;
    const byte LedLight = D6;
    //не используемый блок
    const String apiKey = "I7I84BBE02Z0LZ8G";  // replace with your channel’s thingspeak API key,
    const char* server = "api.thingspeak.com";

#endif // config.hpp
