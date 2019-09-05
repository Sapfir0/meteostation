#ifndef WIFI_H
#define WIFI_H

#include <WString.h>
#include "../types/WeatherType.h"

class WIFI {
    private:
        String _ssid;
        String _password;

    public:
        WIFI(String _ssid, String _password);
        void postToOurServer(WeatherType requestStr);
        bool startWifiModule();
        WeatherType getWeatherData(String units="metric", String lang="en");
};

#endif // WIFI_H