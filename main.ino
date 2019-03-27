#include "DHT.hpp"
#include "LCD.hpp"
#include "RGB.hpp"
//#include "Snake.hpp"
//#include <LiquidCrystalRus.h>  //attention! only for arduino

LCD led;
WIFI esp8266Module;
Gradusnik gradusnik;
RGB diod;

void setup() {
  //noInterrupts();  // no concurency

  gradusnik.start();
  led.startLCD();
  esp8266Module.startWifiModule();
  //diod.startRgb();
  Serial.begin(115200);
  Serial.println("Connecting");

  lcd.clear();  // rewrite
  lcd.print("   Connected!");
  Serial.println("Connected");

  delay(1000);

  //interrupts();  // YES concurency
}

void loop() {
  static int counter = 60;
  static int lag = 5000;
  if (counter == 60) {  // Get new data every n minutes
    counter = 0;
    led.displayGettingData();
    delay(1000);
    esp8266Module.getWeatherData();
    delay(500);
    
    esp8266Module.postToThingSpeak(); //нужно бы постить на свой сервер, но пока его нет, сгодится этот

  } else {
    counter++;
    //led.changeBrightning();
    //delay(100);
    changeValuesOnLCD(); //обычный режим

    //int a = diod.getHorecast(esp8266Module.getTemperature(), esp8266Module.getHumidity(),esp8266Module.getPressure()) ;
    //diod.setColorByRating(a); 

    //Serial.println( diod.getHorecast(esp8266Module.getTemperature(), esp8266Module.getHumidity(),esp8266Module.getPressure()) );
    delay(1000);

  }
}

void changeValuesOnLCD() {
  led.displayWeather( esp8266Module.getWeatherLocation(),
                      esp8266Module.getWeatherDescription(),
                      //esp8266Module.getRussianDescription(esp8266Module.getWeatherID() ),
                      esp8266Module.getCountry() );
  delay(5000);
  led.displayConditions(esp8266Module.getTemperature(), 
                        esp8266Module.getHumidity(), 
                        esp8266Module.toMmRtSt(esp8266Module.getPressure())); //765мм рт ст - норма
  delay(5000);
  
  led.displayDHT(gradusnik.getTemperature(), 
                 gradusnik.getHumidity(), //зимой 30-45%, летом 30-60% нормальная влажность
                 gradusnik.getIluminating());

  delay(5000); //эффект обновления экрана устранен из-за неработающего фоторезистора

/*цель
сделать чтобы как минимум последнее было изменяемым во время работы
то есть, когда мы отрисовываем этот блок, и поменялось значение, хочу
чтобы менялось оно не к следующей отрисовке, а моментально */
}

