#ifndef WIFI_H
#define WIFI_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <ctime>
#include "../types/ourtype.h"

class WIFI {
    private:
        String result;
        String _ssid;
        String _password;

    public:
        WIFI();
        void postToOurServer(Ourtype requestStr);
        void startWifiModule();
        Ourtype getWeatherData();

        String getSSID();
        void setSSID(String ssid);
};

#endif // WIFI_H