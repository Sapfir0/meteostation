//
// Created by avdosev on 31.08.2019.
//

#include "View.h"

#include <map>

#include <services/time/Time.h>
#include <sensors/Gradusnik.h>
#include "../output/LCD.h"
#include "../services/types/WeatherType.h" // ох уж эта строчка

View::View() {

}

const String percent = "%";

void View::displayConditions(float temperature, float humidity, float pressure,
                             const WeatherType::temperatureUnits& degreeUnits=WeatherType::C,
                             const WeatherType::pressureUnits& pressureUnits=WeatherType::hhMg) {
    lcd.clear();
    printTemperature(temperature, degreeUnits);
    printHumidity(humidity);

    lcd.setCursor(0, 1);
    printPressure(pressure, pressureUnits);
}

void View::displayGettingData() {
    lcd.clear();
    lcd.printf("Getting data");
}

void View::displayWeather(String location, String description, String Country) {
    lcd.clear();
    lcd.setCursor(0, 0);

    String firstPart, secondPart;
    firstPart.reserve(30);
    secondPart.reserve(30);

    if (description.length() > 26) { // TODO выводит некорректный вывод, думаю из-за представления кириллических символов
        //то мы выводим только длинное описание погоды в две строки
        int tempI = description.lastIndexOf(" ");
        firstPart = description.substring(0, tempI);
        secondPart = description.substring(tempI, description.length());
        firstPart.trim();
        secondPart.trim();

        lcd.printf(firstPart);
        lcd.setCursor(0, 1);
        lcd.printf(secondPart);
    } else {
        lcd.printf("%s, %s ", location, Country);
        lcd.setCursor(0, 1);
        lcd.printf(description);
    }
}

void View::printTemperature(float temperature, const WeatherType::temperatureUnits& units=WeatherType::C) {
    const char celsiusSymbol = (char) 223;
    String celsius = String(celsiusSymbol) + "C";
    const String fahrenheit = "F";

    lcd.printf("T: ");
    lcd.print(temperature, 1);

    switch (units) {
        case WeatherType::C:
            lcd.print(celsius);
            break;
        case WeatherType::F:
            lcd.printf(fahrenheit);
    }
}

void View::printHumidity(float humidity) {
    lcd.printf(" H:");
    lcd.print(humidity, 0);
    lcd.printf(percent);
}

void View::printPressure(float pressure, const  WeatherType::pressureUnits& units=WeatherType::hhMg) {
    lcd.printf("P: ");
    lcd.print(pressure, 1);

    switch (units) {
        case WeatherType::gPa:
            lcd.printf(" gPa");
            break;
        case WeatherType::hhMg:
            lcd.printf(" mm Hg");
            break;
    }
}


void View::displayConditions(float temperature, float humidity) {
    lcd.clear();
    printTemperature(temperature);
    printHumidity(humidity);

    lcd.setCursor(0, 1);
    lcd.printf("Пустота: ");
    lcd.printf(" ");
}

void View::displayTime(Time t, int hoursMode) {
    lcd.clear();
    lcd.printf("Time:");
    lcd.setCursor(0, 1);
    auto h = t.hour();
    String hour(h%12), min(t.minute()),  half(h<=12 ? "AM" : "PM");
    if (min.length() < 2) min = "0" + min; // для отображения "00-09 min"

    switch (hoursMode) {
        case 12:
            lcd.printf("%s: %s %s", hour, min, half);
            break;
        case 24:
            lcd.printf("%s: %s", String(h), min);
            break;
    }

}

extern WeatherType currentData;
extern Gradusnik gradusnik;
extern int timezone;

void showCurrentWeatherToDisplay(View& dp) {
    dp.displayWeather(currentData.outside.weatherLocation,
                           currentData.outside.weatherDescription,
                           currentData.outside.country);
}

void showCurrentConditionToDisplay(View& dp) {
    dp.displayConditions(currentData.getTemperature(WeatherType::C),
                         currentData.outside.humidity,
                         currentData.getPressure(WeatherType::hhMg), WeatherType::C, WeatherType::hhMg ); // 765мм рт ст - норма
}

void showDisplayDHT(View& dp) {
    dp.displayConditions(gradusnik.getTemperature(), gradusnik.getHumidity());
}

void showCurrentTimeToDisplay(View& dp) {
    Time timeToDisplay = Time::current();
    timeToDisplay.setTimezone(timezone);
    dp.displayTime(timeToDisplay);
}

void View::showNextDisplay() {
    enum class display {
        Start,
        Condition,
        Weather,
        displayDHT,
        Time
    };

    static display currentDisplay = display::Start;
    using callback_t = void(*)(View&); // указатель на функцию
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
    newState.callback(*this);
}

void View::showMessage(String msg) {
    lcd.clear();
    lcd.print(msg);
}
