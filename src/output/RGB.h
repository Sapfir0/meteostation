#ifndef RGB_H
#define RGB_H

#include "services/wifi/WIFI.h"

class RGB {
  private:
    byte rgbPins[3];
  public:
    RGB(byte rgbpin1, byte rgbpin2, byte rgbpin3);

    struct Color {
      uint8_t greenPercent;
      uint8_t bluePercent;
      uint8_t redPercent;
    };

    Color myCurentColor;

    static int weatherDataToRating(float temp, float humidity, float pressure);
    void startRgb();
    void setColorByRating(int raiting);

    bool setPercent();
    //void fading(int red, int green, int blue);
    void fading();
    bool setRGB(uint8_t red, uint8_t green, uint8_t blue);
    void analogWriteRGB(uint8_t red, uint8_t green, uint8_t blue);

    Color getColor();
};

#endif // RGB_H
