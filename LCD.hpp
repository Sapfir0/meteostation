#pragma once
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "WIFI.hpp"

class LCD {
 private:

 public:
  void startLCD();
  void displayWeather(String location, String description, String Country);
  void displayConditions(float Temperature, float Humidity, float Pressure);
  void displayGettingData();
  void displayDHT(float temperature, float humidity, float ilum);
  void loadiiing(); //not used now

  void displayError();

  void printf(const char* str, ...);


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
  lcd.print(" %%");

  lcd.setCursor(0, 1);  
  lcd.print("Sansity: ");
  lcd.print(ilum);
}

//надо сделать свой принтф

//lcd.printf("viudhiud%sfdis%s", " vfhvo ",  " dnois")
//>> viudhiud vfhvo sfdis dnois
void LCD::printf(const char* str, ...) {
  auto nextObj = &str+1;
  while(*str){
    if (*str == '%') {
      if (*(str+1) == 's') {
        lcd.print(*nextObj);
        nextObj++;
      } else {
        lcd.print(*str);
        str++;
      }
    } else {
      lcd.print(*str);
    }
    str++;
  }
  
}


void LCD::displayError() {
  lcd.clear();
  lcd.print("Undefined behavior");
}
