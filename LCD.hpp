#pragma once
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "WIFI.hpp"

class LCD {
 private:
 //локализация етить ее
byte bukva_B[8]   = {0b11110,0b10000,0b10000,0b11110,0b10001,0b10001,0b11110,0b00000}; // Буква "Б"
byte bukva_G[8]   = {0b11111,0b10001,0b10000,0b10000,0b10000,0b10000,0b10000,0b00000}; // Буква "Г"
byte bukva_D[8]   = {0b01111,0b00101,0b00101,0b01001,0b10001,0b11111,0b10001,0b00000}; // Буква "Д"
byte bukva_ZH[8]  = {0b10101,0b10101,0b10101,0b11111,0b10101,0b10101,0b10101,0b00000}; // Буква "Ж"
byte bukva_Z[8]   = {0b01110,0b10001,0b00001,0b00010,0b00001,0b10001,0b01110,0b00000}; // Буква "З"
byte bukva_I[8]   = {0b10001,0b10011,0b10011,0b10101,0b11001,0b11001,0b10001,0b00000}; // Буква "И"
byte bukva_IY[8]  = {0b01110,0b00000,0b10001,0b10011,0b10101,0b11001,0b10001,0b00000}; // Буква "Й"
byte bukva_L[8]   = {0b00011,0b00111,0b00101,0b00101,0b01101,0b01001,0b11001,0b00000}; // Буква "Л"
byte bukva_P[8]   = {0b11111,0b10001,0b10001,0b10001,0b10001,0b10001,0b10001,0b00000}; // Буква "П"
byte bukva_Y[8]   = {0b10001,0b10001,0b10001,0b01010,0b00100,0b01000,0b10000,0b00000}; // Буква "У"
byte bukva_F[8]   = {0b00100,0b11111,0b10101,0b10101,0b11111,0b00100,0b00100,0b00000}; // Буква "Ф"
byte bukva_TS[8]  = {0b10010,0b10010,0b10010,0b10010,0b10010,0b10010,0b11111,0b00001}; // Буква "Ц"
byte bukva_CH[8]  = {0b10001,0b10001,0b10001,0b01111,0b00001,0b00001,0b00001,0b00000}; // Буква "Ч"
byte bukva_Sh[8]  = {0b10101,0b10101,0b10101,0b10101,0b10101,0b10101,0b11111,0b00000}; // Буква "Ш"
byte bukva_Shch[8]= {0b10101,0b10101,0b10101,0b10101,0b10101,0b10101,0b11111,0b00001}; // Буква "Щ"
byte bukva_Mz[8]  = {0b10000,0b10000,0b10000,0b11110,0b10001,0b10001,0b11110,0b00000}; // Буква "Ь"
byte bukva_IYI[8] = {0b10001,0b10001,0b10001,0b11001,0b10101,0b10101,0b11001,0b00000}; // Буква "Ы"
byte bukva_Yu[8]  = {0b10010,0b10101,0b10101,0b11101,0b10101,0b10101,0b10010,0b00000}; // Буква "Ю"
byte bukva_Ya[8]  = {0b01111,0b10001,0b10001,0b01111,0b00101,0b01001,0b10001,0b00000}; // Буква "Я"



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



};
  LiquidCrystal_I2C lcd(0x27, 16, 2);  // Address of your i2c LCD back pack should be updated.


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
  //lcd.print("\x87ndex, RU"); 
  lcd.setCursor(0, 1);
  lcd.print(description);
  
}


void LCD::displayConditions(float Temperature, float Humidity, float Pressure) {
  lcd.clear();  // Printing Temperature
  lcd.print("T:");
  lcd.print(Temperature, 1);
  lcd.print((char)223);
  lcd.print("C H:");
  
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
  static int cursorPosition=0; //не особо важный код для точечек на LCD
  lcd.setCursor(cursorPosition,2); 
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
  lcd.clear();
  lcd.print("Undefined behavior");
}


void LCD::displayGameOver() {//compiling error
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("GAME OVER");
  delay(3000);
}
