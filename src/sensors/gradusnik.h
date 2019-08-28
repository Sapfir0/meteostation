#ifndef GRADUSNIK_H
#define GRADUSNIK_H

#include <DHT.h>

class Gradusnik {
  private:
    DHT dht;
  public:
    Gradusnik(uint8_t dhtPin, uint8_t dhtType);
    float getTemperature();
    float getHumidity();
};

#endif // GRADUSNIK_H

