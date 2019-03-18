#pragma once
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "WIFI.hpp"
// #include <stdarg.h>
// #include <sstream>

class LCD {
 private:

 public:
  void startLCD();
  void displayWeather(String location, String description, String Country);
  void displayConditions(float Temperature, float Humidity, float Pressure);
  void displayGettingData();
  void displayDHT(float temperature, float humidity);
  void loadiiing(); 

  //void printLCD(String s, ...);
  //void printLCD(Arguments const & ... args);

};
  LiquidCrystal_I2C lcd(0x27, 16, 2);  // Address of your i2c LCD back pack should be updated.


void LCD::startLCD() {
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
  lcd.print("   Connecting to");
  lcd.setCursor(0, 1);
  WIFI obj;
  lcd.print(obj.getSSID());


}

void LCD::displayWeather(String location, String description, String Country) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(location);
  lcd.print(", ");
  lcd.print(Country);
  lcd.setCursor(0, 1);
  lcd.print(description);
}

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
  lcd.print(" hPa");
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

void LCD::displayDHT(float temperature, float humidity) {
  lcd.clear();
  lcd.print("T:");
  lcd.print(temperature, 1);
  lcd.print((char)223); //кружок для градуса
  lcd.print("C ");

  lcd.print(" H:");  // Printing Humidity
  lcd.print(humidity, 0);
  lcd.print(" %");
}

//надо сделать свой принтф
// void LCD::printLCD(String s, ...) {

//   lcd.clear();

//   va_list listok;
//   va_start(listok, s);
//   for(auto i = 0; i < *s; i++)  {
//     lcd.print(s);
//   }
//   va_end(listok);
  
// }

// template<typename ... Arguments>
// void LCD::printLCD(Arguments const & ... args)
// {
//     std::stringstream ss;
//     (ss << ... << args);
//     lcd.print(ss);
// }