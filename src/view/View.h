//
// Created by avdosev on 31.08.2019.
//

#ifndef METEOSTATION_2_VIEW_H
#define METEOSTATION_2_VIEW_H

class LCD;
class String;
class Time;

class View {
private:
    LCD& lcd;
public:
    View(LCD &lcd);
    void displayWeather(String location, String description, String Country);
    void displayConditions(float Temperature, float Humidity, float Pressure);
    void displayConditions(float temperature, float humidity);
    void displayGettingData();
    void displayTime(Time t);

};


#endif //METEOSTATION_2_VIEW_H
