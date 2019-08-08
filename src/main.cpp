#include <Esp.h>
#include <Arduino.h>

#include <event_loop.h>
#include <interval.h>
#include <timer.h>

#include "./sensors/gradusnik.hpp"
#include "./output/LCD.hpp"
#include "./output/RGB.hpp"
#include "./services/wifi/WIFI.hpp"
#include "./services/translating/rus.hpp"
#include "config/config.hpp"


EventLoop event_loop;
LCD led; // экран
WIFI esp8266Module; // вифи модуль
Gradusnik gradusnik; // градусник
RGB diod(rgbPins[0], rgbPins[1], rgbPins[2]); // диод
rus rus; // хм

// время в миллисикундах
const int lightDiodeTime = 20*1000; // время между миганием диода
const int changeBrightningTime = 10; // как я то хрень
const int displayOnLCDTime = 6*1000; // время между каждым экраном
const int queryToServerTime = 10*60*1000; // время между отправкой и получением данных на сервер

/**
 * Отправка данных на сервер
 */
void queryToWeatherServer();

/**
 * Сменая цвета диода в зависимости от рейтинга
 */
void setDiodeColorByRating();

void showNextDisplay();

void setup() {
    gradusnik.start();
    led.startLCD();
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

    event_t lightDiode = makeInterval(setDiodeColorByRating, lightDiodeTime, millis);

    event_t delaying(makeInterval(yield, 400, millis));

    event_t changeDisplay(makeInterval(showNextDisplay, displayOnLCDTime, millis));

    // добавляем события
    event_loop.addEvent(delaying);
    event_loop.addEvent(lightDiode);
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
    esp8266Module.getWeatherData();
    delay(1000);    
    esp8266Module.postToOurServer();
}

void setDiodeColorByRating() {
    auto rating = RGB::weatherDataToRating(esp8266Module.getTemperature(),  esp8266Module.getHumidity(),  esp8266Module.getPressure()); // weather rating
    diod.setColorByRating(rating);
}

void showDisplayCondition() {
    led.displayConditions(esp8266Module.getTemperature(), esp8266Module.getHumidity(), esp8266Module.toMmRtSt(esp8266Module.getPressure())); // 765мм рт ст - норма
}

void showDisplayWeather() {
    led.displayWeather(esp8266Module.getWeatherLocation(),
                                // esp8266Module.getWeatherDescription(),
                                rus.getBetterRussianDescription(esp8266Module.getWeatherID()), esp8266Module.getCountry());
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
            showDisplayWeather();
            currentDisplay = display::Weather;
            break;

        case display::Weather:
            showDisplayDHT();
            currentDisplay = display::displayDHT;
            break;

        case display::Start: // чтобы мы начали с Condition
        case display::displayDHT:
            showDisplayCondition();
            currentDisplay = display::Condition;
            break;

        default:
            Serial.print("Error in showNextDisplay");
    }
}