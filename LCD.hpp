#pragma once
//#include <LiquidCrystal_I2C.h>
//#include <Wire.h>
#include "WIFI.hpp"
#include "DHT.hpp"
#include <LCD_1602_RUS.h>
class LCD {
  private:
    WIFI esp;
    Gradusnik grad;
  public:
    void startLCD();
    void displayWeather(String location, String description, String Country);
    void displayConditions(float Temperature, float Humidity, float Pressure);
    void displayGettingData();
    void displayDHT(float temperature, float humidity, float ilum);

    template <typename T, typename... Args>
    void printf(const char *s, T value, Args... args);  // eeeee
    void printf(const char *s);
    void displayGameOver();
    void loadiiing();  // not used now
    void displayError();
    void changeBrightning();

};
LCD_1602_RUS lcd(0x27, 16, 2);

void LCD::startLCD() {
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
  lcd.print("Connecting to");
  lcd.setCursor(0, 1);
  WIFI obj;
  lcd.print(obj.getSSID());
}

void LCD::displayWeather(String location, String description, String Country) {
  lcd.clear();
  lcd.setCursor(0, 0);
  printf("%s, %s ", location, Country);
  lcd.setCursor(0, 1);
  lcd.print(description);

}

void LCD::displayConditions(float Temperature, float Humidity, float Pressure) {
  //  float t = esp.getTemperature();
  //  float h = esp.getHumidity();
  //  float p = esp.getPressure();
  lcd.clear();  // Printing Temperature
  //printf("T: %f", Temperature);
  lcd.print("T:");
  lcd.print(Temperature, 1);
  lcd.print((char)223);
  lcd.print("C H:");
  //printf("C H: %f %%", Humidity);
  lcd.print(Humidity, 0); //0 знаков после запятой
  lcd.print(" %");

  lcd.setCursor(0, 1);
  lcd.print("P: ");
  lcd.print(Pressure, 1);
  lcd.print(" mm Hg");
  //lcd.print(" hPa");
}

void LCD::displayGettingData() {
  lcd.clear();
  lcd.print("Getting data");
}

void LCD::loadiiing() {
  static int cursorPosition = 0; //не особо важный код для точечек на LCD
  lcd.setCursor(cursorPosition, 2);
  lcd.print(".");
  cursorPosition++;
}

void LCD::displayDHT(float temperature, float humidity, float ilum) {
  lcd.clear();
  lcd.print("T:");
  lcd.print(temperature, 1);
  lcd.print((char)223); //кружок для градуса
  lcd.print("C ");

  lcd.print(" H:");  // Printing Humidity
  lcd.print(humidity, 0);
  lcd.print(" %");

  lcd.setCursor(0, 1);
  lcd.print("Sansity: ");
  lcd.print(ilum);
}

//свой принтф
void LCD::printf(const char* s) {
  lcd.print(s);
}
template<typename T, typename... Args>
void LCD::printf(const char *s, T value, Args... args) {
  while (*s) {
    if (*s == '%') {
      if (*(s + 1) == '%') {
        ++s;
      }
      else {
        lcd.print(value);
        s += 2; // работает только для спецификаторов формата из двух символов (напр. %d, %f ).Не будет работать с %5.4f
        printf(s, args...); // вызов происходит даже когда *s == 0, чтобы обнаружить избыточные аргументы
        return;
      }
    }
    lcd.print(*s++);
  }
}

void LCD::displayError() {
  printf("Undefined behavior");
}


void LCD::displayGameOver() {//compiling error
  printf("GAME OVER");
  delay(3000);
}
