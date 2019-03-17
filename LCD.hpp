#include <LiquidCrystal_I2C.h>

class LCD
{
private:
    // static void displayWeather(String location,String description);
    
public:
    void startLCD();
    void displayWeather(String location,String description, String Country);
    void displayConditions(float Temperature,float Humidity, float Pressure); 
    void displayGettingData();
    
};

LiquidCrystal_I2C lcd(0x27, 16, 2);    // Address of your i2c LCD back pack should be updated.


void LCD::startLCD() {
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
  lcd.print("   Connecting");  
}


void LCD::displayWeather(String location,String description, String Country) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(location);
  lcd.print(", ");
  lcd.print(Country);
  lcd.setCursor(0,1);
  lcd.print(description);
}


void LCD::displayConditions(float Temperature,float Humidity, float Pressure) {
 lcd.clear();                            //Printing Temperature
 lcd.print("T:"); 
 lcd.print(Temperature,1);
 lcd.print((char)223);
 lcd.print("C "); 
                                         
 lcd.print(" H:");                       //Printing Humidity
 lcd.print(Humidity,0);
 lcd.print(" %"); 
 
 lcd.setCursor(0,1);                     //Printing Pressure
 lcd.print("P: ");
 lcd.print(Pressure,1);
 lcd.print(" hPa");
}

void LCD::displayGettingData() {
  lcd.clear();
  lcd.print("Getting data");
}
