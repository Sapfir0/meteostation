#include "LCD.hpp"

class Snake  {
private:
    byte square[8] = {0b11111,0b11111,0b11111,0b11111,0b11111,0b11111,0b11111,0b11111};
    int x,y;
    int xspeed, yspeed;
    LCD led;

   public:
    Snake(/* args */);
    int updateSnake(int x, int y);
    void controlment(int LEFT_ARROW, int RIGHT_ARROW, int UP_ARROW, int DOWN_ARROW);

};

Snake::Snake(/* args */) { //потом придумаю способ ввода
    x = 0, y = 0, xspeed = 0, yspeed = 0;
    lcd.clear();
    lcd.createChar(0, square); //змея

}

int Snake::updateSnake(int x, int y) {
  if (x > 16 or x < 0 or y > 2 or y < 0) return -1;
  lcd.clear();
  lcd.setCursor(x, y);
  lcd.print(char(0));
  delay(600);
    
  return 0;
}
//так ебать
//какая идея
//типа задаем декартову сетку
//если -x - идем влево +x - вправо
//-y - вниз, +y - вверх
//и это наш луп, его мы повторяем всегда
void Snake::controlment(int LEFT_ARROW, int RIGHT_ARROW, int UP_ARROW, int DOWN_ARROW) {
  static int resulting;
  if (UP_ARROW) {
    resulting=updateSnake(0,1);
  }  else if (DOWN_ARROW) {
    resulting=updateSnake(0,-1);
  }  else if (RIGHT_ARROW) {
    resulting=updateSnake(1,0);
  }  else if (LEFT_ARROW) {
    resulting=updateSnake(-1,0);
  }
   if( resulting == -1) 
    led.displayGameOver();


}
