#ifndef config.hpp

#include <Arduino.h>

    byte rgbPins[3] = {D5, D8, D7};
    String CityID = "472757"; // Your City ID
    String APIKEY = "9881fdc10d1d14339a3a6514d415efa4";
    const char *ssid = "WiFi-DOM.ru-1520"; // SSID of local network
    const char *password = "sapfir1997";   // Password on network

    String apiKey = "I7I84BBE02Z0LZ8G";  // replace with your channel’s thingspeak API key,
    const char* server = "api.thingspeak.com";
    int DHTPIN = D4;
    int photoresistor = A0;
    int LedLight = D6;


#endif // config.hpp
