#include <Arduino.h>
#include <event_loop.h>
#include <interval.h>

#include "config/config.h"
#include "config/pins.h"

#include "sensors/Gradusnik.h"

#include "services/wifi/WIFI.h"
#include "services/types/WeatherType.h"
#include "services/time/Time.h"

#include "view/View.h"

EventLoop event_loop;
WIFI esp8266Module(ssid, password); // вифи модуль
View display;

Gradusnik gradusnik(DHTPIN, DHTTYPE); // градусник
WeatherType currentData;

// время в миллисикундах
const int displayOnLCDTime = 6*1000; // время между каждым экраном
const int queryToServerTime = 10*60*1000; // время между отправкой и получением данных на сервер

/**
 * Отправка данных на сервер
 */
void queryToWeatherServer();

void setup() {
    Serial.begin(115200);
    display.showMessage("Connecting...");
    bool connectedWifi = esp8266Module.startWifiModule();
    String WifiConnectStr = connectedWifi ? "   Connected!" : "Not connected :(";
    display.showMessage(WifiConnectStr);
    Serial.println(WifiConnectStr);
    delay(100);

    Time::updateFromNTP();
    queryToWeatherServer(); // первый запуск который должен быть всегда

    event_t queryToServer(makeInterval(queryToWeatherServer, queryToServerTime, millis));
    event_t changeDisplay(makeInterval([](){
        display.showNextDisplay();
    }, displayOnLCDTime, millis));

    // добавляем события
    event_loop.addEvent(queryToServer);
    event_loop.addEvent(changeDisplay);
}

void loop() {
    if (event_loop.isRunning())
        event_loop.runNext();
}

void queryToWeatherServer() {
    display.displayGettingData();
    delay(100);
    currentData = esp8266Module.getWeatherData("metric", "en");
    delay(100);    
    esp8266Module.postToOurServer(currentData);
}