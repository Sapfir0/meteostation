#pragma once
#include "WIFI.hpp"


class RGB
{
private:
  const byte rgbPins[3] = {5,3,4};
  int dim = 1;

  public:
    // struct Color  {
    //     uint8_t greenPercent;
    //     uint8_t bluePercent;
    //     uint8_t redPercent;
    // };


    //int getCurrentWeatherID();
    void setColor(int currentWeatherID);
    double getHorecast(float temp, float humidity, float pressure);

};

void RGB::startRgb() {
    for(byte i=0; i<3; i++){
        pinMode( rgbPins[i], OUTPUT );
    }
}

void RGB::setColor(double raiting) {
    //   // код хех
    // for(int i=255; i>=0; i--){
    //     analogWrite( rgbPins[0], i/dim );
    //     analogWrite( rgbPins[1], (255-i)/dim );
    //     delay(10);
    // }
    // // гасим зеленый, параллельно разжигаем синий
    // for(int i=255; i>=0; i--){
    //     analogWrite( rgbPins[1], i/dim );
    //     analogWrite( rgbPins[2], (255-i)/dim );
    //     delay(10);
    // }
    // // гасим синий, параллельно разжигаем красный
    // for(int i=255; i>=0; i--){
    //     analogWrite( rgbPins[2], i/dim );
    //     analogWrite( rgbPins[0], (255-i)/dim );
    //     delay(10);
    // }
}

double RGB::getHorecast(float temp, float hum, float pressure) {
  double raiting = 100;
  float tempRaiting=1, humRaiting=1, pressRaiting=1;
  if (temp <= -20 or temp >= 40) tempRating = 0.1;
  else if (temp > -20 and temp <= 0 or temp < 40 and temp >= 30)    tempRating = 0.3;
  else if ( temp > 0 and temp<10 or temp<30 and temp > 20 )    tempRating = 0.5;
  else    tempRating = 0.9;

/////////////////////////////////////////////////
//////////////////Блок для других рейтингов
/////////////////////////////////////////////////
  
  
  raiting *= tempRaiting * humRaiting * pressRaiting;
  return raiting;
}

