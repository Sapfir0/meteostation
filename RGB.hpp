#pragma once
#include "WIFI.hpp"

class RGB {
 private:
  const byte rgbPins[3] = {5, 3, 4};

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
  void fading(int red, int green, int blue);
  bool setRGB(uint8_t red, uint8_t green, uint8_t blue);
  void analogWriteRGB(uint8_t red, uint8_t green, uint8_t blue);

  Color getColor();
};

void RGB::startRgb() { analogWriteRGB(0, 255, 0); }

void RGB::setColorByRating(int raiting) {
  // код хех
  if (raiting >= 75) {
    setRGB(93, 161, 48);  //зеленый
  } else if (raiting < 75 and raiting >= 50) {
    setRGB(245, 208, 51);  //рыжый
  } else if (raiting < 50 and raiting > 25) {
    setRGB(254, 254, 34);  //желтый
  } else if (raiting <= 25) {
    setRGB(139, 0, 0);  //красный
  }
  //потом вызывать фейд
}

void RGB::analogWriteRGB(uint8_t red, uint8_t green, uint8_t blue) {
  analogWrite(rgbPins[0], red);
  analogWrite(rgbPins[1], green);
  analogWrite(rgbPins[2], blue);
}

bool RGB::setRGB(uint8_t red, uint8_t green, uint8_t blue) {
  if (red > 255 or red < 0 or green > 255 or green < 0 or blue > 255 or blue < 0)
    return false;
  analogWriteRGB(red, green, blue);

  myCurentColor.redPercent = red;
  myCurentColor.greenPercent = green;
  myCurentColor.bluePercent = blue;
  return true;
}

RGB::Color RGB::getColor() {  ///////////////////
  return myCurentColor;
}

int RGB::getHorecast(float temp, float hum, float press) {
  int raiting = 100;
  float tempRating = 1, humRating = 1, pressRating = 1;
  if (temp <= -20 or temp >= 40)
    tempRating = 0.1;
  else if (temp > -20 and temp < 0 or temp < 40 and temp >= 30)
    tempRating = 0.5;
  else if (temp >= 0 and temp < 10 or temp < 30 and temp > 20)
    tempRating = 0.7;
  else
    tempRating = 1.0;

  Serial.println("TempRating: ");
  Serial.println(tempRating);
  /////////////////////////////////////////////////
  //////////////////Блок для других рейтингов
  ////////////////////////////////////////////////////
  //собрать класетр на малинке
  if (press > 755 and press > 766)
    pressRating = 1.0;
  else if (press > 720 and press <= 780)
    pressRating = 0.8;
  else if (press > 850 or press < 560)
    pressRating = 0.3;
  else if (press <= 850 and press > 780 or press >= 560 and press <= 720)
    pressRating = 0.5;
  else
    pressRating = 1.0;

  Serial.println("pressRating: ");
  Serial.println(pressRating);

  raiting *= tempRating * humRating * pressRating;
  return raiting;
}

//мб сюда принимать структуру
void RGB::fading(int red, int green, int blue) {  //эффект мерцания
  analogWriteRGB(red, green, blue);
  for (int fadeValue = 30; fadeValue <= 255; fadeValue += 5) {
    analogWriteRGB(fadeValue, fadeValue, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }
  delay(300);
  for (int fadeValue = 255; fadeValue >= 30; fadeValue -= 5) {
    analogWriteRGB(fadeValue, fadeValue, fadeValue);
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
  }
  delay(300);
}
