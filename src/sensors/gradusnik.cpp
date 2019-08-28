#include "gradusnik.h"

#include <DHT.h>

extern const uint8_t analogPin;

Gradusnik::Gradusnik(uint8_t dhtPin, uint8_t dhtType) :
        dht(dhtPin, dhtType) {
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

float Gradusnik::getValueFromAnalogPort(const uint8_t port=analogPin) { 
    return analogRead(port);  // сюда может быть подлючен фоторезистор либо потенциометтр 
}


void Gradusnik::changeBrightning() {
    int brightn = getValueFromAnalogPort(analogPin) / 4; 
    //возвращаемое значение с порта - 1024 - приводим к 256
    analogWrite(D6, brightn);
}