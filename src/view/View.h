//
// Created by avdosev on 31.08.2019.
//

#pragma once

#include <services/types/WeatherType.h>
#include <output/LCD.h>

class LCD;
class String;
class Time;

class View {
private:
    LCD lcd;
public:
    View();
    void displayWeather(String location, String description, String Country);
    void displayConditions(float temperature, float humidity, float pressure, 
                           const WeatherType::temperatureUnits& degreeUnits,
                           const WeatherType::pressureUnits& pressureUnits);
    void showNextDisplay();
    void displayConditions(float temperature, float humidity);
    void displayGettingData();
    void displayTime(Time t, int hoursMode=24);
    void printHumidity(float humidity);
    void printPressure(float pressure, const WeatherType::pressureUnits& units);
    void printTemperature(float temperature, const  WeatherType::temperatureUnits& units);
    void showMessage(String msg);
};
