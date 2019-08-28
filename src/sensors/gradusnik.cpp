#include <DHT.h> 
#include "gradusnik.h"
#include "../config/config.h"

extern const uint8_t DHTPIN;

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

