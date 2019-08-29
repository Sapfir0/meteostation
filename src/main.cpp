#include <Arduino.h>
#include <event_loop.h>
#include <interval.h>

#include "sensors/gradusnik.h"
#include "output/LCD.h"
#include "services/wifi/WIFI.h"
#include "services/convertors/rus.h"
#include "config/config.h"
#include "services/types/ourtype.h"
#include "services/time/Time.h"

EventLoop event_loop;
WIFI esp8266Module; // вифи модуль
LCD led; // экран
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

void showNextDisplay();

void setup() {
    led.changeBrightning();
    esp8266Module.startWifiModule();	
    Serial.begin(115200);
    led.clear(); // rewrite
    led.printf("   Connected!");
    Serial.println("Connected");
    delay(200);

    Time::updateFromNTP();

    queryToWeatherServer(); // первый запуск который должен быть всегда

    event_t timeCheker(makeInterval([](){
        Serial.println(asctime(Time::current().tmStruct()));
    }, 5000, millis));
    event_t queryToServer(makeInterval(queryToWeatherServer, queryToServerTime, millis));
    event_t changeDisplay(makeInterval(showNextDisplay, displayOnLCDTime, millis));

    event_t changeBrightning(makeInterval([]() {
        led.changeBrightning();
    }, changeBrightningTime, millis));

    // добавляем события
    event_loop.addEvent(queryToServer);
    event_loop.addEvent(changeBrightning);
    event_loop.addEvent(changeDisplay);
    event_loop.addEvent(timeCheker);
}

void loop() {
    if (event_loop.isRunning())
        event_loop.runNext();
}

void queryToWeatherServer() {
    led.displayGettingData();
    delay(100);
    currentData = esp8266Module.getWeatherData("metric", "ru");
    delay(100);    
    esp8266Module.postToOurServer(currentData);
}


void showDisplayCondition(Ourtype type) {
    led.displayConditions(type.getTemperature(type.C), 
                          type.outside.humidity, 
                          type.getPressure(type.hhMg) ); // 765мм рт ст - норма
}

void showDisplayWeather(Ourtype type) {
    led.displayWeather(type.outside.weatherLocation,
                                type.getWeatherDescription(type.EN),
                                type.outside.country);
}

void showDisplayDHT() {
    led.displayConditions(gradusnik.getTemperature(), gradusnik.getHumidity());
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