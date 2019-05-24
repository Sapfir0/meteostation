#pragma once
#include "../services/wifi/WIFI.hpp"
#include "../sensors/DHT.hpp"
#include <LCD_1602_RUS.h>

class LCD {
  private:
    WIFI esp;
    Gradusnik grad;
  public:
    void startLCD();
    void displayWeather(String location, String description, String Country);
    void displayConditions(float Temperature, float Humidity, float Pressure);
    void displayGettingData();
    void displayDHT();

    template <typename T, typename... Args>
    void printf(const char *s, T value, Args... args);  // eeeee
    void printf(const char *s);
    void displayGameOver();
    void loadiiing();  // not used now
    void displayError();
    void changeBrightning();

};

LCD_1602_RUS lcd(0x27, 16, 2);

