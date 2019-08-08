//#pragma once
#ifndef GRADUSNIK_H
#define GRADUSNIK_H

class Gradusnik {
  private:
    float temperature;
    float humidity;
    float illumination;

  public:
    Gradusnik();
    float getTemperature();
    float getHumidity();
    void start();
    float getIluminating();
    void changeBrightning();
    int analyzeEnivromentQuality();
};

#endif // GRADUSNIK_H

