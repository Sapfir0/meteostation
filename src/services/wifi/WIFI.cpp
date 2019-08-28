#include <ESP8266WiFi.h>
#include "../json/jsonParse.h"
#include "../http/http.h"
#include "../../config/config.h"

extern WiFiClient client;

WIFI::WIFI() {
    this->_ssid = ssid;
    this->_password = password;
}

Ourtype WIFI::getWeatherData()  { // client function to send/receive GET request data.
    String url = "id=" + CityID +"&units=metric&APPID=" + APIKEY;
    getQuery("api.openweathermap.org", "/data/2.5/weather", url);
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
    else {
      Serial.println("connection successful");
    }
    String requestStr = data.toString(data);
    postQuery(ourServer, routing, requestStr);
}


void WIFI::startWifiModule() {
    WiFi.begin(_ssid, _password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(50);
        Serial.println("Connection isnt successful");
    }
}

String WIFI::getSSID() {
    return _ssid;
}
