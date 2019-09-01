#ifndef LCD_H
#define LCD_H

#include <WString.h>

class Time;

class LCD {
  public:
    LCD();

    template <typename T, typename... Args>
    void printf(const char *s, T value, Args... args) {
        while ( *s) {
            if ( *s == '%') {
                if ( *(s + 1) == '%') {
                    ++s;
                } else {
                    this->print(value);
                    s += 2; // работает только для спецификаторов формата из двух символов (напр. %d, %f ).Не будет работать с %5.4f
                    printf(s, args...); // вызов происходит даже когда *s == 0, чтобы обнаружить избыточные аргументы
                    return;
                }
            }
            this->print( *s++);
        }
    }
    void printf(const char *s);
    void printf(String s);

    void print(float num, int base);
    void print(char ch);
    void print(String s);

    void clear();

    void setCursor(uint8_t x, uint8_t y);
    float getValueFromAnalogPort(const uint8_t port);

};

#endif // LCD_H


