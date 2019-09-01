//
// Created by avdosev on 31.08.2019.
//

#include "View.h"

#include <services/time/Time.h>
#include "output/LCD.h"
#include "services/types/ourtype.h" // ох уж эта строчка

View::View(LCD &lcd) : lcd(lcd) {

}

const String percent = "%";

void View::displayConditions(float temperature, float humidity, float pressure,
                             Ourtype::temperatureUnits degreeUnits=Ourtype::C,
                             Ourtype::pressureUnits pressureUnits=Ourtype::hhMg) {
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
    int tempI = 0;

    if (description.length() > 26) { // TODO выводит некорректный вывод, думаю из-за представления кириллических символов
        //то мы выводим только длинное описание погоды в две строки
        for (int i = 26; i > 0; i--) { // вот же хуевая хуйня ща тебя перехуячу
            if (description[i] == ' ') { //выбираем символ с которого будем делать перенос - это будет максимально близкий к 16 пробел
                tempI = i; //нам не нужен пробел
                break;
            }
        }
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

void View::printTemperature(float temperature, Ourtype::temperatureUnits units=Ourtype::C) {
    const char celsiusSymbol = (char) 223;
    String celsius = String(celsiusSymbol) + "C";
    const String fahrenheit = "F";

    lcd.printf("T: ");
    lcd.print(temperature, 1);

    switch (units) {
        case Ourtype::C:
            lcd.print(celsius);
            break;
        case Ourtype::F:
            lcd.printf(fahrenheit);
    }
}

void View::printHumidity(float humidity) {
    lcd.printf(" H:");
    lcd.print(humidity, 0);
    lcd.printf(percent);
}

void View::printPressure(float pressure, Ourtype::pressureUnits units=Ourtype::hhMg) {
    lcd.printf("P: ");
    lcd.print(pressure, 1);

    switch (units) {
        case Ourtype::gPa:
            lcd.printf(" gPa");
            break;
        case Ourtype::hhMg:
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

void View::displayTime(Time t) {
    lcd.clear();
    lcd.printf("Time:");
    lcd.setCursor(0, 1);
    auto h = t.hour();
    String hour(h%12), min(t.minute()),  half(h<=12 ? "AM" : "PM");
    if (min.length() < 2) min = "0" + min; // для отображения "00-09 min"
    lcd.printf("%s: %s %s", hour, min, half);
}