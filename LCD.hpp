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

String getRussianDescription(int weatherID);



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

String LCD::getRussianDescription(int weatherID) {
  //map<char, String> mapa;

  String thunderstorm = "гроза";
  String with = " c ";
  String with2 = " co ";
  String drizzle = "морось";
  String rain = "дожд";
  String weakIy = "слабый";
  String weakAya = "слабая";
  String heavyIy = "сильный";
  String heavyAya = "сильная";
  String heavyIm = "сильным";
  String grad = "град";
  String gololed = "гололедица";
  String moros = "моросящий";
  String moderate = "умеренный";
  String sneg = "снег";
  String snegOm = "снегом";

  String rainEm = "дождем";
  String rainB = "дождь";
  String heavyRainB = "ливень";
  String fog = "туман";
  String snow = "снегопад";
  String mestami = "местами";
  String freezing = "замерзающий";
  String shower = "ливневый";
  String small = "небольшая";
  String sep = ",";
  

  switch (weatherID)  {
    case 200:      return thunderstorm + with2 + weakIy + rainEm; //гроза со слабым доджем
    case 201:      return thunderstorm +' ' + with  + rainEm; //гроза с дождем 
    case 202:      return thunderstorm + with + heavyIm + rainEm;
    case 210:      return weakAya  + thunderstorm;
    case 211:      return thunderstorm;
    case 212:      return heavyAya  + thunderstorm;
    case 221:      return mestami + thunderstorm;
    case 230:      return thunderstorm + sep + weakAya  + drizzle;
    case 231:      return thunderstorm + sep + drizzle;
    case 232:      return thunderstorm + sep + heavyAya + drizzle;

    case 300:      return weakAya + drizzle; //слабая морось
    case 301:      return drizzle;
    case 302:      return heavyAya + drizzle;
    case 310:      return "Слабо"+ moros + rainB;
    case 311:      return moros  + rainB;
    case 312:      return heavyAya + "из" + moros;
    case 313:      return rainB + "и" + drizzle;
    case 321:      return drizzle;

    case 500:     return weakIy  + rainB; //легкий дождь
    case 501:     return moderate +rainB;
    case 502:     return heavyIy + rainB;//сильный дождь
    case 503:     return heavyRainB; //ливень
    case 504:     return heavyIy +heavyRainB; //экстремальный дождь
    case 511:     return freezing  + rainB; //замерзающий дождь
    case 520:     return moderate +heavyRainB; //слабый ливень
    case 521:     return heavyRainB; //ливень
    case 522:     return heavyIy + heavyRainB; //сильный ливень
    case 531:     return mestami + heavyRainB; //местами ливень

    case 600:     return weakIy  + snow;	  
    case 601:     return snow;
    case 602:     return heavyIy + snow	; 
    case 611:     return gololed	  ;
    case 612:     return small  + gololed;
    case 613:     return 	grad  ;
    case 615:     return weakIy + rainB + with2 + snegOm ;  
    case 616:     return rainB + with2 + snegOm ;
    case 620:     return weakIy + grad;
    case 621:     return shower + snegOm ;
    case 622:     return heavyIy + shower + sneg ;

    case 701:     return fog;
    case 711:     return "дымка"	;
    case 721:     return "мгла"	;
    case 731:     return "песчаная буря";
    case 741:     return "густой"+fog;
    case 751:     return "песочно";
    case 761:     return "пыльно"	;
    case 762:     return "ВУЛКАНИЧЕСКИЙ ПЕПЕЛ ГОСПОДИ МЫ ВСЕ УМРЕМ";
    case 771:     return "шквал	";
    case 781:     return "торнадо" ;

    case 800:     return "ясно " ;

    case 801:     return "Немного облачно";
    case 802:     return mestami+"облачно";
    case 803:     return "облачно с прояснениями";
    case 804:     return "пасмурно 	";
    default:  return  "ERROR";
  }
  return "ERROR X2";
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
