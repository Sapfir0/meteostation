#pragma once

#include "DHT.h"

#define DHTPIN D4
#define photoresistor A0
#define LedLight D6

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
