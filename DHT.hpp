#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

class Gradusnik {
 private:
  float temperature;
  float humidity;

 public:
  float getTemperature();
  float getHumidity();
  void setTemperature(float temperature);
  void setHumidity(float humidity);
  void start();
};

float Gradusnik::getTemperature() {
  temperature = dht.readTemperature();
  return temperature;
}
float Gradusnik::getHumidity() {
  humidity = dht.readHumidity();
  return humidity;
}
void Gradusnik::start() { dht.begin(); }
