#pragma once

#include "./config/config.hpp"
#include "../sensors/DHT.hpp"

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
    float getTemperature();
    float getHumidity();
    void start();
    float getIluminating();
    void changeBrightning();
    int analyzeEnivromentQuality();
};
