#pragma once

#include "DHT.h"

#define DHTPIN 4
#define photoresistor A0

DHT dht(DHTPIN, DHT11);


class Gradusnik {
 private:
  float temperature;
  float humidity;
  float illumination;

 public:
  float getTemperature();
  float getHumidity();
  // void setTemperature(float temperature);
  // void setHumidity(float humidity);
  void start();
  float getIluminating();

int analyzeEnivromentQuality();
};

void Gradusnik::start() {   
  pinMode(A0, INPUT); //унести в dht блок
  pinMode(4, INPUT);
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

float Gradusnik::getIluminating() { //при максиммальной освещенности 0
  illumination = analogRead(photoresistor); //при минимальной 1024
  return illumination;
}

int Gradusnik::analyzeEnivromentQuality() {

}
