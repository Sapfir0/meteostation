#ifndef GRADUSNIK_H
#define GRADUSNIK_H

class Gradusnik {
  public:
    Gradusnik();
    float getTemperature();
    float getHumidity();
    void changeBrightning();
    float getValueFromAnalogPort(const uint8_t port);
};

#endif // GRADUSNIK_H

