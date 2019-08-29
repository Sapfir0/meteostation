#ifndef WIFI_H
#define WIFI_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <ctime>
#include "../types/ourtype.h"

class WIFI {
    private:
        String _ssid;
        String _password;

    public:
        WIFI(String _ssid, String _password);
        void postToOurServer(Ourtype requestStr);
        void startWifiModule();
        Ourtype getWeatherData(const String& units="metric", const String& lang="en");

};

#endif // WIFI_H