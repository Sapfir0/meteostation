#include "./sensors/gradusnik.hpp"
#include "./output/LCD.hpp"
#include "./output/RGB.hpp"
#include "./services/wifi/WIFI.hpp"
#include "./services/translating/rus.hpp"
#include <Esp.h>
#include <event_loop.h>
#include <interval.h>
#include <timer.h>

LCD led;
WIFI esp8266Module;
Gradusnik gradusnik;
RGB diod;
rus rus;

int lightDiodeTime = 20000;
int changeBrightningTime = 10;
int displayOnLCDTime =  5000;
int queryToServerTime = 60000;


uint32_t tiker() {
    return millis();
}

EventLoop event_loop;

bool queryToWeatherServer(bool firstRun=false) { 
  led.displayGettingData();
  delay(200);
  esp8266Module.getWeatherData();
  delay(1000);
  if(!firstRun) //перезапускаем только если это не 1 запуск
    ESP.reset(); //АХАХАХ я просто жестко перезапускаю ардинку
  esp8266Module.postToOurServer();
  return false; // не хочу тут просто возвращать фолс
}

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

  queryToWeatherServer(true); // первый запуск который должен быть всегда

  event_t queryToServer((Event*) new Interval([](){
      queryToWeatherServer();
    }, queryToServerTime, tiker)); 

  event_t display1((Event*) new Interval([](){
      led.displayConditions(esp8266Module.getTemperature(),
                            esp8266Module.getHumidity(),
                            esp8266Module.toMmRtSt(esp8266Module.getPressure())); //765мм рт ст - норма
    }, displayOnLCDTime, tiker)); 

  event_loop.addEvent((Event*) new Timer([&event_loop](){
    event_t display2((Event*) new Interval([](){  
        led.displayWeather( esp8266Module.getWeatherLocation(),
                            //esp8266Module.getWeatherDescription(),
                            rus.getBetterRussianDescription( esp8266Module.getWeatherID() ),
                            esp8266Module.getCountry() );
      }, displayOnLCDTime, tiker)); 
      event_loop.addEvent(display2);
   }, 5000, tiker)); 

  event_loop.addEvent((Event*) new Timer([&event_loop](){
    event_t display3((Event*) new Interval([](){
        led.displayDHT();
      }, displayOnLCDTime, tiker)); 
    event_loop.addEvent(display3);
  }, 10000, tiker)); 

  event_t changeBrightning((Event*) new Interval([](){
        gradusnik.changeBrightning();
    }, changeBrightningTime, tiker)); 

  event_t lightDiode((Event*) new Interval([](){
      static int a = diod.getHorecast(esp8266Module.getTemperature(), esp8266Module.getHumidity(), esp8266Module.getPressure()); //лол я прошу диод дать прогноз че за херня
      diod.setColorByRating(a);
    }, lightDiodeTime, tiker)); 

    event_loop.addEvent(lightDiode);
    event_loop.addEvent(changeBrightning);
    event_loop.addEvent(display1);

    
    event_loop.addEvent(queryToServer);

    event_loop.exec(); // запускаем цикл событий

}

void loop() { }
