#include <ESP8266WiFi.h>
#include "./WIFI.h"
#include "../json/jsonParse.h"
#include "../http/http.h"
#include "../../config/config.h"
#include "output/ArduinoSerialLogging.h"

WiFiClient client;  // не хочу пока никуда его экспортить


WIFI::WIFI(String _ssid, String _password) : _ssid(_ssid), _password(_password) {
    // TODO поля классы по-прежнему пустые. Что делать?
    Debug() << this->_ssid << "\n" << this->_password << "\n";
}


Ourtype WIFI::getWeatherData(String units, String lang)  { // client function to send/receive GET request data.
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
        Info() << ("connection with" + meteoserver + "failed");
        return;
    }
    Info() << "connection successful";
    String requestStr = data.toString();
    String url = meteoserver + routing;
    post(url, requestStr);
}


bool WIFI::startWifiModule() {
    WiFi.begin(_ssid, _password);
    while (WiFi.status() != WL_CONNECTED) {
        if (WiFi.status() == WL_CONNECT_FAILED) {
            Fatal() << ("Bad ssid or password");
            return false;
        }
        delay(250);
        Info() << ("Connection isn't successful");
    }
    Info() << "Local ip: " << WiFi.localIP().toString() << "\n";
    return true;

}


