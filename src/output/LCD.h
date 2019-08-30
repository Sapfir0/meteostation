#ifndef LCD_H
#define LCD_H

#include <WString.h>

class Time;

class LCD {
  public:
    LCD();
    void displayWeather(String location, String description, String Country);
    void displayConditions(float Temperature, float Humidity, float Pressure);
    void displayConditions(float temperature, float humidity);
    void displayGettingData();
    void displayTime(Time t);

    template <typename T, typename... Args>
    void printf(const char *s, T value, Args... args);  // eeeee
    void printf(const char *s);
    void printf(String s);
    void clear();

    void changeBrightning();
    float getValueFromAnalogPort(const uint8_t port);

};

#endif // LCD_H


