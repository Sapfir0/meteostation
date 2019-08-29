#include "Gradusnik.h"
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

