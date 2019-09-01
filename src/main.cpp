#include <Arduino.h>
#include <event_loop.h>
#include <interval.h>

#include "config/config.h"

#include "output/LCD.h"

#include "sensors/Gradusnik.h"

#include "services/wifi/WIFI.h"
#include "services/types/ourtype.h"
#include "services/time/Time.h"

#include <view/View.h>

EventLoop event_loop;
WIFI esp8266Module(ssid, password); // вифи модуль
LCD led; // экран
View display(led);

Gradusnik gradusnik(DHTPIN, DHTTYPE); // градусник
Ourtype currentData;

// время в миллисикундах
const int changeBrightningTime = 10; // смена яркости экрана через потенциометр
const int displayOnLCDTime = 6*1000; // время между каждым экраном
const int queryToServerTime = 10*60*1000; // время между отправкой и получением данных на сервер

/**
 * Отправка данных на сервер
 */
void queryToWeatherServer();

void setup() {
    Serial.begin(115200);
    led.changeBrightning();
    esp8266Module.startWifiModule();
    led.clear(); // rewrite
    led.printf("   Connected!");
    Serial.println("Connected");
    delay(100);

    Time::updateFromNTP();
    queryToWeatherServer(); // первый запуск который должен быть всегда

    event_t queryToServer(makeInterval(queryToWeatherServer, queryToServerTime, millis));
    event_t changeDisplay(makeInterval([](){
        display.showNextDisplay();
    }, displayOnLCDTime, millis));

    event_t changeBrightning(makeInterval([]() {
        led.changeBrightning();
    }, changeBrightningTime, millis));

    // добавляем события
    event_loop.addEvent(queryToServer);
    event_loop.addEvent(changeBrightning);
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