#include "DHT.h"

#define DHTPIN 2
#define photoresistor A0

DHT dht(DHTPIN, DHT11);

class Gradusnik {
 private:
  float temperature;
  float humidity;
  float illumination;
  //vector<float> pressure;

 public:
  float getTemperature();
  float getHumidity();
  void setTemperature(float temperature);
  void setHumidity(float humidity);
  void start();
  float getIluminating();

int analyzeEnivromentQuality();
};

void Gradusnik::start() { dht.begin(); }

float Gradusnik::getTemperature() {
  temperature = dht.readTemperature();
  return temperature;
}
float Gradusnik::getHumidity() {
  humidity = dht.readHumidity();
  return humidity;
}

float Gradusnik::getIluminating() {
  illumination = analogRead(photoresistor);
  return illumination;
}

//int Gradusnik::getForecast(float press) {
//  pressure.append(press);
//}

int Gradusnik::analyzeEnivromentQuality() {

}
