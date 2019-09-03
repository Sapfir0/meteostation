#include <ESP8266WiFi.h>
#include "./WIFI.h"
#include "../json/jsonParse.h"
#include "../http/http.h"
#include "../../config/config.h"

WiFiClient client;  // не хочу пока никуда его экспортить


WIFI::WIFI(String _ssid, String _password) {
    this->_ssid = _ssid;
    this->_password = _password;
    // TODO поля классы по-прежнему пустые. Что делать?
}


Ourtype WIFI::getWeatherData(const String& units, const String& lang)  { // client function to send/receive GET request data.
    String params = "?id=" + CityID // либо сделать передачу русских букв по http либо переводить через rus.cpp
                + "&units=" + units
                + "&lang=" + lang
                + "&APPID=" + APIKEY;
    String url = openweathermapServer + params;
    String result = get(url);

    Ourtype type(result);
    return type;
}


void WIFI::postToOurServer(Ourtype data) {
    int port = 80;
    if (!client.connect(meteoserver, port)) {
        Serial.println("connection with" + meteoserver + "failed");
        return;
    }
    Serial.println("connection successful");
    String requestStr = data.toString();
    String url = meteoserver + routing;
    post(url, requestStr);
}


bool WIFI::startWifiModule() {
    WiFi.begin(_ssid, _password);
    while (WiFi.status() != WL_CONNECTED) {
        if (WiFi.status() == WL_CONNECT_FAILED) {
            Serial.println("Bad ssid or password");
            return false;
        }
        delay(250);
        Serial.println("Connection isn't successful");
    }
    return true;
}


