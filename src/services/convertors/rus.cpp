#include "rus.h"

String getBetterRussianDescription(String weatherDescription) {  // TODO rewrite
  weatherDescription.trim();
  //проходим по строке и убираем двойной пробел
  for(uint i = 0; i < weatherDescription.length()-2; i++)  {
    if (weatherDescription[i] == ' ' and weatherDescription[i+1] == ' ') {//почему не isSpace
      weatherDescription.remove(i,1); //удалить пробел
    }
  }
//   if (temp.length() > 16) { //если строка длиннее 16 символов
//  //то делаем перенос следующих символов на следующую строчку   
//   }
  return weatherDescription;
}
