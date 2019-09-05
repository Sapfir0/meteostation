#ifndef WIFI_H
#define WIFI_H

#include <WString.h>
#include "../types/ourtype.h"

class WIFI {
    private:
        String _ssid;
        String _password;

    public:
        WIFI(String _ssid, String _password);
        void postToOurServer(Ourtype requestStr);
        bool startWifiModule();
        Ourtype getWeatherData(String units="metric", String lang="en");
};

#endif // WIFI_H