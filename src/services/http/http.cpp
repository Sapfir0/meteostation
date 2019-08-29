#include "http.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

String get(String url) {
    return request("get", url);
}

String post(String url, String data) { // передается в body
    return request("post", url, data);
}

String request(String method, String url, String data) {
    HTTPClient http;
    String payload = "";
    int httpCode = 0;

    http.begin(url);
    if (method == "get") {
        httpCode = http.GET();
        payload = http.getString();
    }
    else if (method == "post") {
        http.addHeader("Content-Type", "application/x-www-form-urlencoded; charset=utf-8");
        http.addHeader("User-Agent", "ArduinoWiFi/1.1");
        httpCode = http.POST(data);
        payload = http.getString();
    }
    else {
        Serial.println("Undefined method");
    }

    if (httpCode <= 0) {
        Serial.println("Bad request code " + String(httpCode));
    }
    http.end();
    Serial.println(payload);
    return payload;
}



