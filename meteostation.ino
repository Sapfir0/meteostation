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
GTimer_ms myTimer5(600000); //запрос к серверу
//так епта
//я разобрался как это робит
//типа в момент запуска время 0
//через 5с mytimer2 срабатывает, но время не сбрасывается

void setup() {
  gradusnik.start();
  led.startLCD();
  gradusnik.changeBrightning();

  esp8266Module.startWifiModule();
  Serial.begin(115200);
  Serial.println("Connecting");

  lcd.clear();  // rewrite
  lcd.print("   Connected!");
  Serial.println("Connected");

  delay(200);


myTimer2.setInterval(5000);   // настроить интервал 5 сек
myTimer2.setMode(MANUAL); // ручной режим
myTimer1.setMode(MANUAL); // ручной режим
myTimer15.setMode(MANUAL); // ручной режим
myTimer5.setMode(MANUAL); // ручной режим
}

void loop() {
  static int counter = 0;
  static int logger = 0;
  

  if (myTimer5.isReady() || counter == 0) {
    counter++;
    led.displayGettingData();
    delay(200);
    esp8266Module.getWeatherData();
    delay(200);
    esp8266Module.postToThingSpeak();  //нужно бы постить на свой сервер, но
    //пока его нет, сгодится этот
  }

  
  if (myTimer1.isReady() ) {
    gradusnik.changeBrightning();
    myTimer1.reset();
  }
  if (myTimer2.isReady() && logger == 0 ) {
    led.displayWeather( esp8266Module.getWeatherLocation(),
                        esp8266Module.getWeatherDescription(),
                        //esp8266Module.getRussianDescription(esp8266Module.getWeatherID() ),
                        esp8266Module.getCountry() );
    logger = 1;
    myTimer2.reset();
    delay(10);// хз чет не робит 
  }
  if (myTimer2.isReady() && logger == 1 ) {
    led.displayConditions(esp8266Module.getTemperature(),
                          esp8266Module.getHumidity(),
                          esp8266Module.toMmRtSt(esp8266Module.getPressure())); //765мм рт ст - норма
    logger = 2;
    myTimer2.reset();
    delay(10);
  }
  if (myTimer2.isReady() && logger == 2) {
    led.displayDHT(gradusnik.getTemperature(),
                   gradusnik.getHumidity(), //зимой 30-45%, летом 30-60% нормальная влажность
                   gradusnik.getIluminating());
    logger = 0;
    myTimer2.reset();
    delay(10);
  }
  if (myTimer15.isReady()) {
    static int a = diod.getHorecast(esp8266Module.getTemperature(), esp8266Module.getHumidity(), esp8266Module.getPressure());
    Serial.println( a );
    diod.setColorByRating(a);
    myTimer15.reset();
  }

//    if (myTimer1.isReady() ) {
//      diod.fading();
//    }
}
