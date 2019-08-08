#include "rus.hpp"

String rus::getBetterRussianDescription(int weatherID) {
  String temp = getRussianDescription(weatherID);
  temp.trim();
  //проходим по строке и убираем двойной пробел
  for(int i = 0; i < temp.length()-2; i++)  {
    if (temp[i] == ' ' and temp[i+1] == ' ') {//почему не isSpace
      temp.remove(i,1); //удалить пробел
    }
  }
//   if (temp.length() > 16) { //если строка длиннее 16 символов
//  //то делаем перенос следующих символов на следующую строчку   
//   }
  return temp;
}



String rus::getRussianDescription(int weatherID) {
  //map<char, String> mapa;
  
  String thunderstorm = " гроза " ;
  String with = " c " ;
  String with2 =  " co " ;
  String drizzle =  " морось " ;
  String weakIy =  " слабый " ;
  String weakIm =  " слабым " ;
  String weakAya =  " слабая " ;
  String heavyIy =  " сильный " ;
  String heavyAya =  " сильная " ;
  String heavyIm =  " сильным " ;
  String grad =  " град " ;
  String gololed =  " гололедица " ;
  String moros =  " моросящий " ;
  String moderate =  " умеренный " ;
  String sneg =  " снег " ;
  String snegOm =  " снегом " ;

  String rainEm =  " дождем " ;
  String rainB =  " дождь " ;
  String heavyRainB =  " ливень " ;
  String fog =  " туман " ;
  String snow =  " снегопад " ;
  String mestami =  " местами " ;
  String freezing =  " замерзающий " ;
  String shower =  " ливневый " ;
  String small =  " небольшая " ;
  String sep =  ", ";

  String slabo =  " слабо " ;
  String andW =  " и " ;
  String from =  " из " ;
  String smoke =  " дымка " ;
  String mist =   " мгла " ;
  String sandStorm =  " песчаная буря " ;
  String dense =   " густой " ;
  String sandy =   " песочно " ;
  String dusty =   " пыльно " ;
  String OMG =  " ВУЛКАНИЧЕСКИЙ ПЕПЕЛ ГОСПОДИ МЫ ВСЕ УМРЕМ " ;
  String squall =  " шквал " ;
  String tornado =   " торнадо " ;
  String clearSky =   " ясно  " ;
  String lowCloudy =   " немного облачно " ;
  String cloudy =   " облачно " ;
  String cloudyWithClarifications =   " облачно с прояснениями " ;
  String murky =  " пасмурно " ;

    switch (weatherID) {
      case 200:        return thunderstorm + with2 + weakIm + rainEm;  //гроза со слабым доджем
      case 201:        return thunderstorm + with + rainEm;  //гроза с дождем
      case 202:        return thunderstorm + with + heavyIm + rainEm;
      case 210:        return weakAya + thunderstorm;
      case 211:        return thunderstorm;
      case 212:        return heavyAya + thunderstorm;
      case 221:        return mestami + thunderstorm;
      case 230:        return thunderstorm + sep + weakAya + drizzle;
      case 231:        return thunderstorm + sep + drizzle;
      case 232:        return thunderstorm + sep + heavyAya + drizzle;

      case 300:        return weakAya + drizzle;  //слабая морось
      case 301:        return drizzle;
      case 302:        return heavyAya + drizzle;
      case 310:        return slabo + moros + rainB;
      case 311:        return moros + rainB;
      case 312:        return heavyAya + from + moros;
      case 313:        return rainB + andW + drizzle;
      case 321:        return drizzle;

      case 500:        return weakIy + rainB;  //легкий дождь
      case 501:        return moderate + rainB;
      case 502:        return heavyIy + rainB;  //сильный дождь
      case 503:        return heavyRainB;  //ливень
      case 504:        return heavyIy + heavyRainB;  //экстремальный дождь
      case 511:        return freezing + rainB;  //замерзающий дождь
      case 520:        return moderate + heavyRainB;  //слабый ливень
      case 521:        return heavyRainB;  //ливень
      case 522:        return heavyIy + heavyRainB;  //сильный ливень
      case 531:        return mestami + heavyRainB;  //местами ливень

      case 600:        return weakIy + snow;
      case 601:        return snow;
      case 602:        return heavyIy + snow;
      case 611:        return gololed;
      case 612:        return small + gololed;
      case 613:        return grad;
      case 615:        return weakIy + rainB + with2 + snegOm;
      case 616:        return rainB + with2 + snegOm;
      case 620:        return weakIy + grad;
      case 621:        return shower + snegOm;
      case 622:        return heavyIy + shower + sneg;

      case 701:        return fog;
      case 711:        return smoke;
      case 721:        return mist;
      case 731:        return sandStorm;
      case 741:        return dense + fog;
      case 751:        return sandy;
      case 761:        return dusty;
      case 762:        return OMG;
      case 771:        return squall;
      case 781:        return tornado;

      case 800:        return clearSky;

      case 801:        return lowCloudy;
      case 802:        return mestami + cloudy;
      case 803:        return cloudy;
      case 804:        return murky;
      default:
        return "ERROR";
    }
    return "ERROR X2";
}

#include <map>

String rus::urlEncode(String rusString) {
    // когда-нибудь я дореализую эту шнягу, но пока буду юзать инглиш
    // первый обязательно должон иметь перегруженный оператор меньше
    std::map <String, const char*> russianChars = {
        { "а", "%D0%B0" },
        { "б", "%D0%B1" }, 
        { "в", "%D0%B2" },
        { "г", "%D0%B3" },
        { "д", "%D0%B4" },
        { "е", "%D0%B5" }, 
        { "ё", "%D1%91" }, //искл
        { "ж", "%D0%B6" },
        { "з", "%D0%B7" },
        { "и", "%D0%B8" }, 
        { "й", "%D0%B9" },
        { "к", "%D0%BA" },
        { "л", "%D0%BB" },
        { "м", "%D0%BC" }, 
        { "н", "%D0%BD" },
        { "п", "%D0%BF" },
        { "р", "%D1%80" }, //+1
        { "с", "%D1%81" }, 
        { "т", "%D1%82" },
        { "у", "%D1%83" },
        { "ф", "%D1%84" },
        { "х", "%D1%85" }, 
        { "ц", "%D1%86" },
        { "ч", "%D1%87" },
        { "ш", "%D1%88" },
        { "щ", "%D1%89" }, 
        { "ъ", "%D1%8A" },
        { "ы", "%D1%8B" },
        { "ь", "%D1%8C" },
        { "э", "%D1%8D" }, 
        { "ю", "%D1%8E" },
        { "я", "%D1%8F" },
        { "А", "%D0%90" },
        { "Б", "%D0%91" }, 
        { "В", "%D0%92" },
        { "Г", "%D0%93" },
        { "Д", "%D0%94" },
        { "Е", "%D0%95" }, 
        { "Ё", "%D0%81" }, //искл
        { "Ж", "%D0%96" },
        { "З", "%D0%97" },
        { "И", "%D0%98" }, 
        { "Й", "%D0%99" },
        { "К", "%D0%9A" },
        { "Л", "%D0%9B" },
        { "М", "%D0%9C" }, 
        { "Н", "%D0%9D" },
        { "П", "%D0%9F" },
        { "Р", "%D0%A0" },
        { "С", "%D0%A1" }, 
        { "Т", "%D0%A2" },
        { "У", "%D0%A3" },
        { "Ф", "%D0%A4" },
        { "Х", "%D0%A5" }, 
        { "Ц", "%D0%A6" },
        { "Ч", "%D0%A7" },
        { "Ш", "%D0%A8" },
        { "Щ", "%D0%A9" }, 
        { "Ъ", "%D0%AA" },
        { "Ы", "%D0%AB" },
        { "Ь", "%D0%AC" },
        { "Э", "%D0%AD" }, 
        { "Ю", "%D0%AE" },
        { "Я", "%D0%AF" }
    };

    String res = "";

    for(unsigned int i = 0; i < rusString.length(); i++) {
        auto itOnRusChar = russianChars.find(String(rusString[i]));
        if (itOnRusChar == russianChars.end()) {
            res += rusString[i]; // не преобразовываем
        } else {
            res += itOnRusChar->second; // пушим в новом виде
        }
    }

    return res;
}