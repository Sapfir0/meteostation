#ifndef GRADUSNIK_H
#define GRADUSNIK_H

class Gradusnik {
  public:
    Gradusnik();
    float getTemperature();
    float getHumidity();
    void changeBrightning();
    float getValueFromAnalogPort();
};

#endif // GRADUSNIK_H

