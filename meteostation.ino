#include "./config/config.hpp"
#include "./sensors/gradusnik.hpp"
#include "./output/LCD.hpp"
#include "./output/RGB.hpp"
#include "./services/wifi/WIFI.hpp"
#include "./services/translating/rus.hpp"
#include <Esp.h>
#include <event_loop.h>
#include <interval.h>
#include <timer.h>

LCD led;
WIFI esp8266Module;
Gradusnik gradusnik;
RGB diod(rgbPins[0], rgbPins[1], rgbPins[2]);
rus rus;

const int lightDiodeTime = 20000;
const int changeBrightningTime = 10;
const int displayOnLCDTime = 20000;
const int queryToServerTime = 600000;

uint32_t tiker() {
    return millis();
}

EventLoop event_loop;

/**
 * пояснение к странной функции
 */
void queryToWeatherServer() {
    led.displayGettingData();
    delay(200);
    esp8266Module.getWeatherData();
    delay(1000);    
    esp8266Module.postToOurServer();
}

void showDisplayCondition() {
    led.displayConditions(esp8266Module.getTemperature(), esp8266Module.getHumidity(), esp8266Module.toMmRtSt(esp8266Module.getPressure())); //765мм рт ст - норма
}

void showDisplayWeather() {
    led.displayWeather(esp8266Module.getWeatherLocation(),
                                //esp8266Module.getWeatherDescription(),
                                rus.getBetterRussianDescription(esp8266Module.getWeatherID()), esp8266Module.getCountry());
}


void setDiodeColorByRating() {
    auto rating = RGB::weatherDataToRating(esp8266Module.getTemperature(),  esp8266Module.getHumidity(),  esp8266Module.getPressure()); // weather rating
    diod.setColorByRating(rating);
}

void setup() {
    gradusnik.start();
    led.startLCD();
    gradusnik.changeBrightning();
    esp8266Module.startWifiModule();
    Serial.begin(115200);
    Serial.println("Connecting");
    lcd.clear(); // rewrite
    lcd.print("   Connected!");
    Serial.println("Connected");

    delay(200);

    queryToWeatherServer(); // первый запуск который должен быть всегда

    event_t queryToServer(makeInterval([]() {
        queryToWeatherServer();
    }, queryToServerTime, tiker));


    event_t changeBrightning(makeInterval([]() {
        gradusnik.changeBrightning();
    }, changeBrightningTime, tiker));

    event_t lightDiode = makeInterval(setDiodeColorByRating, lightDiodeTime, tiker);

    event_t delaying(makeInterval([]() {
        yield();
    }, 500, tiker));

    // добавляем события
    event_loop.addEvent(delaying);
    event_loop.addEvent(lightDiode);
    event_loop.addEvent(queryToServer);
    event_loop.addEvent(changeBrightning);

    event_loop.addEvent(makeTimer([&event_loop]() {
        event_loop.addEvent(makeInterval(showDisplayWeather, displayOnLCDTime, tiker));
    }, 5000, tiker));

    event_loop.addEvent(makeTimer([&event_loop]() {
        event_t display3(makeInterval([]() {
            led.displayDHT();
        }, displayOnLCDTime, tiker));
        event_loop.addEvent(display3);
    }, 10000, tiker));

    event_loop.addEvent(makeInterval(showDisplayCondition, displayOnLCDTime, tiker));

    event_loop.exec(); // запускаем цикл событий
}

void loop() {
    // do loop
}
