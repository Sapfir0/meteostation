#include "DHT.hpp"
#include "LCD.hpp"
#include "RGB.hpp"
//#include <LiquidCrystalRus.h>  //attention! only for arduino
#include "GyverTimer.h"

LCD led;
WIFI esp8266Module;
Gradusnik gradusnik;
RGB diod;

GTimer_ms myTimer1(10); //обновление экрана
GTimer_ms myTimer15(20000); //смена цвета диода и дача прогноза
GTimer_ms myTimer2(5000); //1 окно
//GTimer_ms myTimer3(15000); //2 окно
//GTimer_ms myTimer4(30000); //3 окно
GTimer_ms myTimer5(600000); //запрос к серверу
//так епта
//я разобрался как это робит
//типа в момент запуска время 0
//через 5с mytimer2 срабатывает, но время не сбрасывается
void setup() {
  gradusnik.start();
  led.startLCD();
  esp8266Module.startWifiModule();
  Serial.begin(115200);
  Serial.println("Connecting");

  lcd.clear();  // rewrite
  lcd.print("   Connected!");
  Serial.println("Connected");

  delay(300);
}

void loop() {
  static int counter = 0;

  if (myTimer5.isReady() || counter == 0) {
    counter++;
    led.displayGettingData();
    delay(200);
    esp8266Module.getWeatherData();
    delay(200);
    esp8266Module.postToThingSpeak();  //нужно бы постить на свой сервер, но
    //пока его нет, сгодится этот
  }
  static int logger = 0;
  if (myTimer1.isReady() ) {
    gradusnik.changeBrightning();
  }
  if (myTimer2.isReady() && logger == 0 ) {
    led.displayWeather( esp8266Module.getWeatherLocation(),
                        esp8266Module.getWeatherDescription(),
                        //esp8266Module.getRussianDescription(esp8266Module.getWeatherID() ),
                        esp8266Module.getCountry() );
    logger = 1;
  }
  if (myTimer2.isReady() && logger == 1 ) {
    led.displayConditions(esp8266Module.getTemperature(),
                          esp8266Module.getHumidity(),
                          esp8266Module.toMmRtSt(esp8266Module.getPressure())); //765мм рт ст - норма
    logger = 2;
  }
  if (myTimer2.isReady() && logger == 2) {
    led.displayDHT(gradusnik.getTemperature(),
                   gradusnik.getHumidity(), //зимой 30-45%, летом 30-60% нормальная влажность
                   gradusnik.getIluminating());
    logger = 0;
  }
  if (myTimer15.isReady()) {
    static int a = diod.getHorecast(esp8266Module.getTemperature(), esp8266Module.getHumidity(), esp8266Module.getPressure());
    Serial.println( a );
    diod.setColorByRating(a);
  }

//    if (myTimer1.isReady() ) {
//      diod.fading();
//    }
}

void changeValuesOnLCD() {
  delay(5000); //эффект обновления экрана устранен из-за неработающего фоторезистора
  /*цель
    сделать чтобы как минимум последнее было изменяемым во время работы
    то есть, когда мы отрисовываем этот блок, и поменялось значение, хочу
    чтобы менялось оно не к следующей отрисовке, а моментально */
}
