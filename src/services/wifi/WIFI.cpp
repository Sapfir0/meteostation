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


WeatherType WIFI::getWeatherData(String units, String lang)  { // client function to send/receive GET request data.
    String params = "?id=" + CityID // либо сделать передачу русских букв по http либо переводить через rus.cpp
                + "&units=" + units
                + "&lang=" + lang
                + "&APPID=" + APIKEY;
    String url = openweathermapServer + params;
    String result = get(url);

    WeatherType type(result);
    return type;
}


void WIFI::postToOurServer(WeatherType data) {
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
    constexpr unsigned long time_to_delay = 250;
    constexpr uint8_t max_delay_count = 10*1000/time_to_delay; // предполагаем что 10сек (в миллисикундах) достаточно для коннекта
    WiFi.mode(WIFI_STA);
    WiFi.hostname(hostname);
    WiFi.begin(_ssid, _password);

    uint8_t count_of_delay = 0;
    while (WiFi.status() != WL_CONNECTED) {
        if (WiFi.status() == WL_CONNECT_FAILED) {
            Fatal() << ("Bad ssid or password");
            return false;
        }

        if (count_of_delay >= max_delay_count) {
            Fatal() << "Maximum count of delays exceeded";
            return false;
        }

        Info() << "Connection isn't successful"
               << "Try connect...";

        delay(time_to_delay);
        count_of_delay++;
    }
    Info() << hostname;
    Info() << "Local ip: " << WiFi.localIP().toString() << "\n";
    WiFi.printDiag(Serial);
    return true;

}


