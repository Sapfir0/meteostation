#include <ESP8266WiFi.h>
#include "../../sensors/gradusnik.hpp"
#include "../translating/rus.hpp"
#include "../json/jsonParse.hpp"
#include "../http/http.hpp"

extern WiFiClient client;

#include "../../config/config.hpp"


Ourtype WIFI::getWeatherData()  { // client function to send/receive GET request data.
    http req;
    String requestStr = "id=" + CityID +"&units=metric&APPID=" + APIKEY;
    req.getQuery("api.openweathermap.org", "/data/2.5/weather", requestStr);
    result = req.getResponseFromServer(result);

    Ourtype type(result);
    return type;
}


void WIFI::postToOurServer(Ourtype data) {
    int port = 80;
    if (!client.connect(ourServer, port)) { //чет не работет, если сюда переменную кинуть
        Serial.println("connection with" + ourServer + "failed");
        return;
    }
    else {
      Serial.println("connection successful");
    }
    http req; 
    String requestStr = data.toString(data);
    req.postQuery(ourServer, "/meteostationData", requestStr);
}


void WIFI::startWifiModule() {
    WiFi.begin(_ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connection isnt successful");
    }
    
}


const char * WIFI::getSSID() {
    return _ssid;
}

void WIFI::setSSID(const char * ssid) {
    _ssid = ssid;
}