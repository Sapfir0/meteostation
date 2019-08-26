#ifndef WIFI_H
#define WIFI_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <ctime>
#include "../types/ourtype.h"

class WIFI {
    private:
        String result;

    public:
        void postToOurServer(Ourtype requestStr);
        void startWifiModule();
        Ourtype getWeatherData();

        const char * getSSID();
        void setSSID(const char * ssid);
};

#endif // WIFI_H