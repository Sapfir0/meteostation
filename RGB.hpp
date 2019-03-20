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
    struct currentColor
    {
        uint8_t greenPercent;
        uint8_t bluePercent;
        uint8_t redPercent;
    };

  public:
    uint8_t goToBlueColor(uint8_t currentColor);
    uint8_t goToRedColor(uint8_t currentColor);
    uint8_t goToGreenColor(uint8_t currentColor);

    int getCurrentWeater();

};

 int RGB::getCurrentWeater() {
     WIFI esp;
     return esp.getWeatherID;
 }
