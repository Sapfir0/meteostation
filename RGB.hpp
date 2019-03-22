#pragma once

#define RED 5 // Присваиваем имя RED для пина 11
#define GREEN 3 // Присваиваем имя GREEN для пина 12
#define BLUE 4 // Присваиваем имя BLUE для пина 13


#include "WIFI.hpp"

//менять цвет при более-менее критических событиях
//дождь - синий свет
//снег - голубой
//

class RGB
{
private:

  public:
    struct Color  {
        uint8_t greenPercent;
        uint8_t bluePercent;
        uint8_t redPercent;
    };


    //int getCurrentWeatherID();
    void setColor(int currentWeatherID);
  void setRGB(int r,int g,int b);
};


// int RGB::getCurrentWeatherID() {
//     WIFI esp;
//     return esp.getWeatherID;
// }

// RGB::Color RGB::getCurrentColor() {
//
// }

void RGB::setColor(int currentWeatherID) {
    WiFi esp;
    if ( esp.getTemperature() < ) 
}


