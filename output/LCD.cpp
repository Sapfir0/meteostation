#include "LCD.hpp"

void LCD::displayConditions(float Temperature, float Humidity, float Pressure) {
  //  float t = esp.getTemperature();
  //  float h = esp.getHumidity();
  //  float p = esp.getPressure();
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


void LCD::displayWeather(String location, String description, String Country) {
  lcd.clear();
  lcd.setCursor(0, 0);

  String firstPart, secondPart;
  firstPart.reserve(30);
  secondPart.reserve(30);
  int tempI;
  
  if (description.length() > 26) { //выводит некорректный вывод, думаю из-за представления кириллических символов
    //то мы выводим только длинное описание погоды в две строки
    for (int i = 26; i > 0; i--)    {
      if (description[i] == ' ') { //выбираем символ с которого будем делать перенос - это будет максимально близкий к 16 пробел
        tempI = i; //нам не нужен пробел
        break;
      }
    }
    firstPart = description.substring(0,tempI);
    secondPart = description.substring(tempI,description.length());
    firstPart.trim();
    secondPart.trim();
    
    lcd.print(firstPart);
    lcd.setCursor(0, 1);
    lcd.print(secondPart);
  }
  else {
    printf("%s, %s ", location, Country);
    lcd.setCursor(0, 1);
    lcd.print(description);
  }

}

void LCD::startLCD() {
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
  lcd.print("Connecting to");
  lcd.setCursor(0, 1);
  WIFI obj;
  lcd.print(obj.getSSID());
}



void LCD::loadiiing() {
  static int cursorPosition = 0; //не особо важный код для точечек на LCD
  lcd.setCursor(cursorPosition, 2);
  lcd.print(".");
  cursorPosition++;
}

void LCD::displayDHT() {
  lcd.clear();
  lcd.print("T:");
  lcd.print(grad.getTemperature(), 1);
  lcd.print((char)223); //кружок для градуса

  lcd.print("C  H:");  // Printing Humidity
  lcd.print(grad.getHumidity(), 0);
  lcd.print(" %");

  lcd.setCursor(0, 1);
  lcd.print("Sansity: ");
  lcd.print(grad.getIluminating());
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
