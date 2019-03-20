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
    Color color;
    if (currentWeatherID >= 200 and currentWeatherID <= 232 ) { //Group 2xx: Thunderstorm

    }
    else if (currentWeatherID >= 300 and currentWeatherID <= 321) { //Group 3xx: Drizzle

    }
    else if (currentWeatherID >= 500 and currentWeatherID <= 531) {//Group 5xx: Rain
    
    }
    else if (currentWeatherID >= 600 and currentWeatherID <= 622) { //Group 6xx: Snow
    
    }
    else if (currentWeatherID >= 700 and currentWeatherID <= 781) {//Group 7xx: Atmosphere
    
    }
    else if (currentWeatherID == 800) {//Group 800: Clear
      Serial.println(currentWeatherID);

      for(color.greenPercent=0; color.greenPercent<=255; color.greenPercent++)
        setRGB(color.redPercent, color.greenPercent, color.bluePercent);
    }
    else if (currentWeatherID >= 801 and currentWeatherID <= 804) { //Group 80x: Clouds
    for(color.greenPercent=0; color.greenPercent<=255; color.greenPercent++)
        setRGB(color.redPercent, color.greenPercent, color.bluePercent);
    }
    else {
        //bug();
    }
}


void RGB::setRGB(int r,int g,int b) {
analogWrite(RED,r);
analogWrite(GREEN,g);
analogWrite(BLUE,b);
delay(10);
}
