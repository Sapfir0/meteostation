//#pragma once
#ifndef GRADUSNIK_H
#define GRADUSNIK_H

#include "../config/config.hpp"
#include "DHT.h" //стандартная либа

extern const byte DHTPIN;
extern const byte photoresistor;
extern const byte  LedLight; //соре за глобал переменные, я потом придумаю, как сделать перменные со значениями из-вне членами класса

DHT dht(DHTPIN, DHT11);

class Gradusnik {
  private:
    float temperature;
    float humidity;
    float illumination;

  public:
    Gradusnik();
    float getTemperature();
    float getHumidity();
    void start();
    float getIluminating();
    void changeBrightning();
    int analyzeEnivromentQuality();
};

#endif // GRADUSNIK_H

