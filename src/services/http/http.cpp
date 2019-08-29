#include "http.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

WiFiClient client;

String get(String url) { //http://api.openweathermap.org/data/2.5/uvi/forecast?lat=48.72&lon=44.5&appid=9881fdc10d1d14339a3a6514d415efa4
    return request("get", url);
}

String post(String url, String data) { // вариант с query
    return request("post", url, data);
}

String request(String method, String url, String data) {
    HTTPClient http;
    String payload = "";
    http.begin(url);
    Serial.println(url);
    if (method == "get") {
        int httpCode = http.GET();
        if (httpCode <= 0) {
            Serial.println("Bad get code " + String(httpCode));
        }
        String payload = http.getString();
        Serial.println(payload);
    }
    else if (method == "post") {

        http.addHeader("Content-Type", "text/plain");
        int httpCode = http.POST(data);
        String payload = http.getString();

        if (httpCode != 200) {
            Serial.println("Bad post code " + String(httpCode));
        }
       Serial.println(payload);
    }
    else {
        Serial.println("Undefined method");
        //return false;
    }

    http.end();
    return payload;
}



