#include <DHT.h> 
#include "gradusnik.h"
#include "../config/config.h"

extern const byte DHTPIN;

DHT dht(DHTPIN, DHT11);

Gradusnik::Gradusnik() {
    dht.begin();
}

float Gradusnik::getTemperature() {
    float temperature = dht.readTemperature();
    return temperature;
}

float Gradusnik::getHumidity() {
    float humidity = dht.readHumidity();
    return humidity;
}

float Gradusnik::getValueFromAnalogPort() { 
    return analogRead(photoresistor);  // сюда может быть подлючен фоторезистор либо потенциометтр 
}


void Gradusnik::changeBrightning() {
    int brightn = getValueFromAnalogPort() / 4; 
    //возвращаемое значение с порта - 1024 - приводим к 256
    analogWrite(D6, brightn);
}