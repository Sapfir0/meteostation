//
// Created by avdosev on 31.08.2019.
//

#ifndef METEOSTATION_VIEW_H
#define METEOSTATION_VIEW_H

#include <services/types/ourtype.h>

class LCD;
class String;
class Time;

class View {
private:
    LCD& lcd;
public:
    View(LCD &lcd);
    void displayWeather(String location, String description, String Country);
    void displayConditions(float temperature, float humidity, float pressure, 
                           Ourtype::temperatureUnits degreeUnits,
                           Ourtype::pressureUnits pressureUnits);
    void displayConditions(float temperature, float humidity);
    void displayGettingData();
    void displayTime(Time t);
    void printHumidity(float humidity);
    void printPressure(float pressure, Ourtype::pressureUnits units);
    void printTemperature(float temperature, Ourtype::temperatureUnits units);
};


#endif //METEOSTATION_VIEW_H
