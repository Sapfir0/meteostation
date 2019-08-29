#include <ESP8266WiFi.h>
#include "./WIFI.h"
#include "../json/jsonParse.h"
#include "../http/http.h"
#include "../../config/config.h"

#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
extern WiFiClient client;

WIFI::WIFI() {
    this->_ssid = ssid;
    this->_password = password;
}

Ourtype WIFI::getWeatherData(String units, String lang)  { // client function to send/receive GET request data.
    String params = "?id=" + CityID // либо сделать передачу русских букв по http либо переводить через rus.cpp
                + "&units=" + units
                + "&lang=" + lang
                + "&APPID=" + APIKEY;
    String url = "api.openweathermap.org/data/2.5/weather" + params;
    String result = get(url); // до первого слеша хост, после урл

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
    String url = ourServer + routing;
    post(url, requestStr);
}


void WIFI::startWifiModule() {
    WiFi.begin(_ssid, _password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(50);
        Serial.println("Connection isnt successful");
    }
}

