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
    //void setColor(int currentWeatherID);
    double getHorecast(float temp, float humidity, float pressure);
    void startRgb();
    void setColor(double raiting);


};

void RGB::startRgb() {

    analogWrite(rgbPins[0], 255);
    analogWrite(rgbPins[1], 0);
    analogWrite(rgbPins[2], 0);
}

void RGB::setColor(double raiting) {
      // код хех
    for(int i=255; i>=0; i--){
        analogWrite( rgbPins[0], i/dim );
        analogWrite( rgbPins[1], (255-i)/dim );
        delay(10);
    }
    // гасим зеленый, параллельно разжигаем синий
    for(int i=255; i>=0; i--){
        analogWrite( rgbPins[1], i/dim );
        analogWrite( rgbPins[2], (255-i)/dim );
        delay(10);
    }
    // гасим синий, параллельно разжигаем красный
    for(int i=255; i>=0; i--){
        analogWrite( rgbPins[2], i/dim );
        analogWrite( rgbPins[0], (255-i)/dim );
        delay(10);
    }
}

double RGB::getHorecast(float temp, float hum, float press) {
  double raiting = 100;
  float tempRating=1, humRating=1, pressRating=1;
  if (temp <= -20 or temp >= 40) tempRating = 0.1;
  else if (temp > -20 and temp < 0 or temp < 40 and temp >= 30)    tempRating = 0.5;
  else if ( temp >= 0 and temp<10 or temp<30 and temp > 20 )    tempRating = 0.7;
  else    tempRating = 1.0;
Serial.println("TempRating: ");
Serial.println(tempRating);
/////////////////////////////////////////////////
//////////////////Блок для других рейтингов
////////////////////////////////////////////////////рассказать про технологию
//собрать класетр на малинке
  if (press > 850 or press < 560) pressRating = 0.3;
  else if ( press <=850 and press>780 or press >= 560 and press<=720) pressRating=0.5;
  else if (press >720 and press <= 780 ) pressRating=0.8;
  else if (press>755 and press >766) pressRating=1.0;
  else pressRating=1.0;
  
  Serial.println("pressRating: ");
  Serial.println(pressRating);

  raiting *= tempRating * humRating * pressRating;
  return raiting;
}
