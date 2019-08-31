#include <Arduino.h>
#include <event_loop.h>
#include <interval.h>
#include <map>

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

void showNextDisplay();

void setup() {
    Serial.begin(115200);
    led.changeBrightning();
    esp8266Module.startWifiModule();
    led.clear(); // rewrite
    led.printf("   Connected!");
    Serial.println("Connected");
    delay(200);

    Time::updateFromNTP();

    queryToWeatherServer(); // первый запуск который должен быть всегда

    event_t queryToServer(makeInterval(queryToWeatherServer, queryToServerTime, millis));
    event_t changeDisplay(makeInterval(showNextDisplay, displayOnLCDTime, millis));

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
    currentData = esp8266Module.getWeatherData("metric", "ru");
    delay(100);    
    esp8266Module.postToOurServer(currentData);
}

void showCurrentWeatherToDisplay() {
    display.displayWeather(currentData.outside.weatherLocation,
                       currentData.outside.weatherDescription,
                       currentData.outside.country);
}

void showCurrentConditionToDisplay() {
    display.displayConditions(currentData.getTemperature(Ourtype::C),
                          currentData.outside.humidity,
                          currentData.getPressure(Ourtype::hhMg) ); // 765мм рт ст - норма
}

void showDisplayDHT() {
    display.displayConditions(gradusnik.getTemperature(), gradusnik.getHumidity());
}

void showCurrentTimeToDisplay() {
    Time timeToDisplay = Time::current();
    timeToDisplay.setTimezone(4);
    display.displayTime(timeToDisplay);
}

void showNextDisplay() {
    enum class display {
        Start,
        Condition,
        Weather,
        displayDHT,
        Time
    };

    static display currentDisplay = display::Start;

    struct State {
        display nextState;
        callback_t callback;
    };

    static std::map<display, State> states{
        /* current / next / callback */
        {display::Start, {display::Time, showCurrentWeatherToDisplay}},
        {display::displayDHT, {display::Time, showCurrentWeatherToDisplay}},
        {display::Weather, {display::displayDHT, showDisplayDHT}},
        {display::Condition, {display::Weather, showCurrentConditionToDisplay}},
        {display::Time, {display::Condition, showCurrentTimeToDisplay}}
    };
    // ищем в таблице следующее состояние
    auto states_iterator = states.find(currentDisplay);
    State newState = states_iterator->second;
    // сменяем текущее состояние и выполняем коллбек
    currentDisplay = newState.nextState;
    newState.callback();
}