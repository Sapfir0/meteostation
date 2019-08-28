#include "LCD.h"
#include <LCD_1602_RUS.h>
#include "config/config.h"

LCD_1602_RUS lcd(0x27, 16, 2);

extern const uint8_t analogPin;
char celsiusSymbol = (char) 223;

LCD::LCD() {
    lcd.begin(16, 2);
    lcd.init();
    lcd.backlight();
    lcd.print("Connecting to");
    lcd.setCursor(0, 1);
    lcd.print(ssid);  // не отобразится // хз
}

void LCD::displayConditions(float temperature, float humidity, float pressure) {
    lcd.clear(); 
    lcd.print("T:");
    lcd.print(temperature, 1); //1 знак после запятой
    lcd.print(celsiusSymbol);
    lcd.print("C H:");
    lcd.print(humidity, 0); //0 знаков после запятой
    lcd.print(" %");

    lcd.setCursor(0, 1);
    lcd.print("P: ");
    lcd.print(pressure, 1);
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
    int tempI = 0;

    if (description.length() > 26) { //выводит некорректный вывод, думаю из-за представления кириллических символов
        //то мы выводим только длинное описание погоды в две строки
        for (int i = 26; i > 0; i--) { // вот же хуевая хуйня ща тебя перехуячу
            if (description[i] == ' ') { //выбираем символ с которого будем делать перенос - это будет максимально близкий к 16 пробел
                tempI = i; //нам не нужен пробел
                break;
            }
        }
        firstPart = description.substring(0, tempI);
        secondPart = description.substring(tempI, description.length());
        firstPart.trim();
        secondPart.trim();

        lcd.print(firstPart);
        lcd.setCursor(0, 1);
        lcd.print(secondPart);
    } else {
        printf("%s, %s ", location, Country);
        lcd.setCursor(0, 1);
        lcd.print(description);
    }
}


void LCD::displayConditions(float temperature, float humidity) {
    lcd.clear();
    lcd.print("T:");
    lcd.print(temperature, 1);
    lcd.print(celsiusSymbol); 

    lcd.print("C  H:"); // Printing Humidity
    lcd.print(humidity, 0);
    lcd.print(" %");

    lcd.setCursor(0, 1);
    lcd.print("Пустота: ");
    lcd.print(" ");
}

//свой принтф
void LCD::printf(const char* s) {
    lcd.print(s);
}

void LCD::printf(String s) {
    for(int i=0; i<s.length(); i++) {
        lcd.print(s[i]);
    }
}

template <typename T, typename...Args>
void LCD::printf(const char *s, T value, Args...args) {
    while ( *s) {
        if ( *s == '%') {
            if ( *(s + 1) == '%') {
                ++s;
            } else {
                lcd.print(value);
                s += 2; // работает только для спецификаторов формата из двух символов (напр. %d, %f ).Не будет работать с %5.4f
                printf(s, args...); // вызов происходит даже когда *s == 0, чтобы обнаружить избыточные аргументы
                return;
            }
        }
        lcd.print( *s++);
    }
}

void LCD::clear() {
    lcd.clear();
}

float LCD::getValueFromAnalogPort(const uint8_t port=analogPin) {
    return analogRead(port);  // сюда может быть подлючен фоторезистор либо потенциометтр
}


void LCD::changeBrightning() {
    int brightn = getValueFromAnalogPort(analogPin) / 4;
    //возвращаемое значение с порта - 1024 - приводим к 256
    analogWrite(D6, brightn);
}