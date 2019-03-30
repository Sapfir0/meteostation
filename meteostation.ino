#include "DHT.hpp"
#include "LCD.hpp"
#include "RGB.hpp"
#include "GyverTimer.h"

LCD led;
WIFI esp8266Module;
Gradusnik gradusnik;
RGB diod;

GTimer_ms changeBrightning(10); //обновление экрана
GTimer_ms lightDiode(20000); //смена цвета диода и дача прогноза
GTimer_ms changeLCD(5000); //1 окно
GTimer_ms queryToServer(600000); //запрос к серверу
GTimer_ms fade(500); //обновление экрана

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

  changeLCD.setMode(MANUAL); // ручной режим
}

void loop() {
  static int counter = 0;
  static int logger = 0;

  if (queryToServer.isReady() || counter == 0) {
    counter++;
    led.displayGettingData();
    delay(200);
    esp8266Module.getWeatherData();
    delay(200);
    esp8266Module.postToThingSpeak();  //нужно бы постить на свой сервер, но
    //пока его нет, сгодится этот
  }


  if (changeBrightning.isReady() ) {
    gradusnik.changeBrightning();
  }
  if (changeLCD.isReady() && logger == 0 ) {
    led.displayWeather( esp8266Module.getWeatherLocation(),
                        // esp8266Module.getWeatherDescription(),
                        esp8266Module.getRussianDescription(esp8266Module.getWeatherID() ),
                        esp8266Module.getCountry() );
    logger = 1;
    changeLCD.reset();
  }
  if (changeLCD.isReady() && logger == 1 ) {
    led.displayConditions(esp8266Module.getTemperature(),
                          esp8266Module.getHumidity(),
                          esp8266Module.toMmRtSt(esp8266Module.getPressure())); //765мм рт ст - норма
    logger = 2;
    changeLCD.reset();
  }
  if (changeLCD.isReady() && logger == 2) {
    led.displayDHT();
    logger = 0;
    changeLCD.reset();
  }
  if (lightDiode.isReady()) {
    static int a = diod.getHorecast(esp8266Module.getTemperature(), esp8266Module.getHumidity(), esp8266Module.getPressure());
    Serial.println( a );
    diod.setColorByRating(a);
  }

//     if (fade.isReady() ) {
//       diod.fading();
//     }
}
