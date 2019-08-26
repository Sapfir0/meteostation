#include <Esp.h>
#include <Arduino.h>

#include <event_loop.h>
#include <interval.h>
#include <timer.h>

#include "sensors/gradusnik.h"
#include "output/LCD.h"
#include "services/wifi/WIFI.h"
#include "services/translating/rus.h"
#include "config/config.h"
#include "services/types/ourtype.h"

EventLoop event_loop;
LCD led; // экран
Gradusnik gradusnik; // градусник
WIFI esp8266Module; // вифи модуль
rus russian; // l18n

Ourtype currentData;
// время в миллисикундах
const int changeBrightningTime = 10; // смена яркости экрана через потенциометр
const int displayOnLCDTime = 6*1000; // время между каждым экраном
const int queryToServerTime = 10*60*1000; // время между отправкой и получением данных на сервер

/**
 * Отправка данных на сервер
 */
void queryToWeatherServer();

void showNextDisplay();

void setup() {
    gradusnik.changeBrightning();
    esp8266Module.startWifiModule();	
    Serial.begin(115200);
    Serial.println("Connecting");
    led.clear(); // rewrite
    led.printf("   Connected!");
    Serial.println("Connected");

    delay(200);

    queryToWeatherServer(); // первый запуск который должен быть всегда

    event_t queryToServer(makeInterval(queryToWeatherServer, queryToServerTime, millis));

    event_t changeBrightning(makeInterval([]() {
        gradusnik.changeBrightning();
    }, changeBrightningTime, millis));

    event_t delaying(makeInterval(yield, 400, millis));

    event_t changeDisplay(makeInterval(showNextDisplay, displayOnLCDTime, millis));

    // добавляем события
    event_loop.addEvent(delaying);
    event_loop.addEvent(queryToServer);
    event_loop.addEvent(changeBrightning);
    event_loop.addEvent(changeDisplay);

    event_loop.exec(); // запускаем цикл событий
}

void loop() {
    // do loop ...
}

void queryToWeatherServer() {
    led.displayGettingData();
    delay(200);
    currentData = esp8266Module.getWeatherData();
    delay(200);    
    esp8266Module.postToOurServer(currentData);
}


void showDisplayCondition(Ourtype type) {
    led.displayConditions(type.outside.temperature, 
                          type.outside.humidity, 
                          type.outside.pressure); // 765мм рт ст - норма
}

void showDisplayWeather(Ourtype type) {
    led.displayWeather(type.outside.weatherLocation,
                                russian.getBetterRussianDescription(type.outside.weatherID), 
                                type.outside.country);
}

void showDisplayDHT() {
    led.displayDHT();
}

void showNextDisplay() {
    enum class display {
        Start,
        Condition,
        Weather,
        displayDHT
    };

    static display currentDisplay = display::Start; 

    switch (currentDisplay) {
        case display::Condition:
            showDisplayWeather(currentData);
            currentDisplay = display::Weather;
            break;

        case display::Weather:
            showDisplayDHT();
            currentDisplay = display::displayDHT;
            break;

        case display::Start: // чтобы мы начали с Condition
        case display::displayDHT:
            showDisplayCondition(currentData);
            currentDisplay = display::Condition;
            break;

        default:
            Serial.print("Error in showNextDisplay");
    }
}