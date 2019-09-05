#ifndef GRADUSNIK_H
#define GRADUSNIK_H

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

#endif // GRADUSNIK_H

