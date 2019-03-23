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

String parsingDescr(int weatherID);



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
  //lcd.print("BO\2\3O\3PA\1, RU"); 
  lcd.setCursor(0, 1);
 lcd.print(description);
  //parsingDescr(903);
}

String LCD::parsingDescr(int weatherID) {
  //map<char, String> mapa;

  lcd.createChar(0, bukva_L);      // Создаем символ под номером 1
  lcd.write(0);

  lcd.createChar(1, bukva_G);      // Создаем символ под номером 2
  lcd.createChar(2, bukva_I);      // Создаем символ под номером 2
  lcd.createChar(3, bukva_IY);      // Создаем символ под номером 2
  lcd.createChar(4, bukva_Mz);      // Создаем символ под номером 2
  lcd.createChar(5, bukva_IYI);      // Создаем символ под номером 2
  lcd.createChar(6, bukva_Y);      // Создаем символ под номером 2

  lcd.createChar(7, bukva_B);      // Создаем символ под номером 2
  lcd.createChar(8, bukva_CH);      // Создаем символ под номером 2
  lcd.createChar(8, bukva_P);      // Создаем символ под номером 2
  lcd.createChar(9, bukva_Ya);      // Создаем символ под номером 2

  String light = "C\0A\7\5\3";
  String heavy = "C\2\0\4H\5\3";
  String fog = "T\6MAH";
  String cloudy = "O\7\0A\8HO";
  String with = " C ";
  String broken = "\8PO\8CHTH\2\9M\2";


  switch (weatherID)
  {
    case 200:
      
      break;
  
    case 903:
      break;
    default:
      break;
  }
  return "AF";
}
/*
Group 2xx: Thunderstorm
ID 	Main 	Description 	Icon
200 	Thunderstorm 	thunderstorm with light rain 	11d
201 	Thunderstorm 	thunderstorm with rain 	11d
202 	Thunderstorm 	thunderstorm with heavy rain 	11d
210 	Thunderstorm 	light thunderstorm 	11d
211 	Thunderstorm 	thunderstorm 	11d
212 	Thunderstorm 	heavy thunderstorm 	11d
221 	Thunderstorm 	ragged thunderstorm 	11d
230 	Thunderstorm 	thunderstorm with light drizzle 	11d
231 	Thunderstorm 	thunderstorm with drizzle 	11d
232 	Thunderstorm 	thunderstorm with heavy drizzle 	11d
Group 3xx: Drizzle
ID 	Main 	Description 	Icon
300 	Drizzle 	light intensity drizzle 	09d
301 	Drizzle 	drizzle 	09d
302 	Drizzle 	heavy intensity drizzle 	09d
310 	Drizzle 	light intensity drizzle rain 	09d
311 	Drizzle 	drizzle rain 	09d
312 	Drizzle 	heavy intensity drizzle rain 	09d
313 	Drizzle 	shower rain and drizzle 	09d
314 	Drizzle 	heavy shower rain and drizzle 	09d
321 	Drizzle 	shower drizzle 	09d
Group 5xx: Rain
ID 	Main 	Description 	Icon
500 	Rain 	light rain 	10d
501 	Rain 	moderate rain 	10d
502 	Rain 	heavy intensity rain 	10d
503 	Rain 	very heavy rain 	10d
504 	Rain 	extreme rain 	10d
511 	Rain 	freezing rain 	13d
520 	Rain 	light intensity shower rain 	09d
521 	Rain 	shower rain 	09d
522 	Rain 	heavy intensity shower rain 	09d
531 	Rain 	ragged shower rain 	09d
Group 6xx: Snow
ID 	Main 	Description 	Icon
600 	Snow 	light snow 	13d
601 	Snow 	Snow 	13d
602 	Snow 	Heavy snow 	13d
611 	Snow 	Sleet 	13d
612 	Snow 	Light shower sleet 	13d
613 	Snow 	Shower sleet 	13d
615 	Snow 	Light rain and snow 	13d
616 	Snow 	Rain and snow 	13d
620 	Snow 	Light shower snow 	13d
621 	Snow 	Shower snow 	13d
622 	Snow 	Heavy shower snow 	13d
Group 7xx: Atmosphere
ID 	Main 	Description 	Icon
701 	Mist 	mist 	50d
711 	Smoke 	Smoke 	50d
721 	Haze 	Haze 	50d
731 	Dust 	sand/ dust whirls 	50d
741 	Fog 	fog 	50d
751 	Sand 	sand 	50d
761 	Dust 	dust 	50d
762 	Ash 	volcanic ash 	50d
771 	Squall 	squalls 	50d
781 	Tornado 	tornado 	50d
Group 800: Clear
ID 	Main 	Description 	Icon
800 	Clear 	clear sky 	01d 01n
Group 80x: Clouds
ID 	Main 	Description 	Icon
801 	Clouds 	few clouds: 11-25% 	02d 02n
802 	Clouds 	scattered clouds: 25-50% 	03d 03n
803 	Clouds 	broken clouds: 51-84% 	04d 04n  облачно с прояснениями
804 	Clouds 	overcast clouds: 85-100% */


void LCD::displayConditions(float Temperature, float Humidity, float Pressure) {
  lcd.clear();  // Printing Temperature
  lcd.print("T:");
  lcd.print(Temperature, 1);
  lcd.print((char)223);
  lcd.print("C ");

  lcd.print(" H:");  // Printing Humidity
  lcd.print(Humidity, 0);
  lcd.print(" %");

  lcd.setCursor(0, 1);  // Printing Pressure
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

//надо сделать свой принтф

//lcd.printf("viudhiud%sfdis%s", " vfhvo ",  " dnois")
//>> viudhiud vfhvo sfdis dnois
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
//  lcd.clear;
//  lcd.setCursor(0, 0);
//  lcd.print("GAME OVER");
//  delay(3000);
}
