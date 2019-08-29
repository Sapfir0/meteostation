#include <ESP8266WiFi.h>
#include "./WIFI.h"
#include "../json/jsonParse.h"
#include "../http/http.h"
#include "../../config/config.h"

extern WiFiClient client;

WIFI::WIFI() {
    this->_ssid = ssid;
    this->_password = password;
}

Ourtype WIFI::getWeatherData(String units, String lang)  { // client function to send/receive GET request data.
    String params = "id=" + CityID // либо сделать передачу русских букв по http либо переводить через rus.cpp
                + "&units=" + units
                + "&lang=" + lang
                + "&APPID=" + APIKEY;
    getQuery("api.openweathermap.org", "/data/2.5/weather", params);
    String result = getResponseFromServer(result);

    Ourtype type(result);
    return type;
}


void WIFI::postToOurServer(Ourtype data) {
    int port = 80;
    if (!client.connect(ourServer, port)) { 
        Serial.println("connection with" + ourServer + "failed");
        return;
    }

    Serial.println("connection successful");
    String requestStr = data.toString();
    postQuery(ourServer, routing, requestStr);
}


void WIFI::startWifiModule() {
    WiFi.begin(_ssid, _password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(50);
        Serial.println("Connection isnt successful");
    }
}

