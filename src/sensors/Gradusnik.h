#pragma once

#include <cinttypes>

class DHT;

class Gradusnik {
  private:
    DHT* dht;
  public:
    Gradusnik(uint8_t dhtPin, uint8_t dhtType);
    ~Gradusnik();

    float getTemperature();
    float getHumidity();

};
