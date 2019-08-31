#include "LCD.h"
#include <LCD_1602_RUS.h>
#include <services/time/Time.h>
#include "config/config.h"

LCD_1602_RUS lcd(0x27, 16, 2);

extern const uint8_t analogPin;

LCD::LCD() {
    lcd.begin(16, 2);
    lcd.init();
    lcd.backlight();
    lcd.print("Connecting to");
    lcd.setCursor(0, 1);
    Serial.println(ssid);
    lcd.print(ssid);  // TODO к этому момент ssid пустой. почему?
}

void LCD::print(float num, int base) {
    lcd.print(num, base);
}

void LCD::print(char ch) {
    lcd.print(ch);
}

void LCD::print(String s) {
    lcd.print(s);
}

void LCD::setCursor(uint8_t x, uint8_t y) {
    lcd.setCursor(x, y);
}

//свой принтф
void LCD::printf(const char* s) {
    lcd.print(s);
}

void LCD::printf(String s) {
    for(unsigned int i=0; i<s.length(); i++) {
        lcd.print(s[i]);
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