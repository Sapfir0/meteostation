#ifndef LCD_H
#define LCD_H

#include <Arduino.h>

class LCD {
  public:
    LCD();
    void displayWeather(String location, String description, String Country);
    void displayConditions(float Temperature, float Humidity, float Pressure);
    void displayConditions(float temperature, float humidity);
    void displayGettingData();

    template <typename T, typename... Args>
    void printf(const char *s, T value, Args... args);  // eeeee
    void printf(const char *s);
    void printf(String s);

    void clear();

    void displayGameOver();
    void loadiiing();  // not used now
    void displayError(String error);
    void changeBrightning();

};

#endif // LCD_H


