#pragma once

#include "config.hpp"
#include "DHT.h"

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

void Gradusnik::start() {
  dht.begin();
}

float Gradusnik::getTemperature() {
  temperature = dht.readTemperature();
  return temperature;
}
float Gradusnik::getHumidity() {
  humidity = dht.readHumidity();
  return humidity;
}

float Gradusnik::getIluminating() { //��� ������������� ������������ 0
  illumination = analogRead(photoresistor); //��� ����������� 1024
  return illumination;
}

int Gradusnik::analyzeEnivromentQuality() {

}

void Gradusnik::changeBrightning() {
  int brightn;
  brightn = getIluminating() / 4; //при минимальной 1024
  //возвращаемое значение с порта - 1024 - приводим к 256
  analogWrite(D6, brightn);
}
