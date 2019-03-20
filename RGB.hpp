#define RED 5 // Присваиваем имя RED для пина 11
#define GREEN 3 // Присваиваем имя GREEN для пина 12
#define BLUE 4 // Присваиваем имя BLUE для пина 13

#pragma once
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


    int getCurrentWeatherID();
    void setColor(RGB::Color, int currentWeatherID);

};


 int RGB::getCurrentWeatherID() {
     WIFI esp;
     return esp.getWeatherID;
 }

 RGB::Color RGB::getCurrentColor() {

 }

void RGB::setColor(RGB::Color, int currentWeatherID) {
    
    if (currentWeatherID >= 200 and currentWeatherID <= 232 ) {

    }
    else if (currentWeatherID >= 300 and currentWeatherID <= 321) {

    }
    else if (currentWeatherID >= 500 and currentWeatherID <= 531) {
    
    }
    else if (currentWeatherID >= 600 and currentWeatherID <= 622) {
    
    }
    else if (currentWeatherID >= 700 and currentWeatherID <= 781) {
    
    }
    else if (currentWeatherID == 800) {
    
    }
    else if (currentWeatherID >= 801 and currentWeatherID <= 804) {
    
    }
    else {
        bug();
    }
}

