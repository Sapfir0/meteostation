#ifndef RGB_H
#define RGB_H

#include "../config/config.hpp"
#include "../services/wifi/WIFI.hpp"

extern const byte rgbPins[3];

class RGB {
  //private:
    
  public:
    struct Color {
      uint8_t greenPercent;
      uint8_t bluePercent;
      uint8_t redPercent;
    };
    Color myCurentColor;

    int getHorecast(float temp, float humidity, float pressure);
    void startRgb();
    void setColorByRating(int raiting);

    bool setPercent();
    //void fading(int red, int green, int blue);
    void fading();
    bool setRGB(uint8_t red, uint8_t green, uint8_t blue);
    void analogWriteRGB(uint8_t red, uint8_t green, uint8_t blue);

    Color getColor();
};

#include "RGB.cpp"

#endif // RGB_H
