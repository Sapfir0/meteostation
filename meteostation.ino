#include "DHT.hpp"
#include "LCD.hpp"
#include "RGB.hpp"
#include "parallel.hpp"

LCD led;
WIFI esp8266Module;
Gradusnik gradusnik;
RGB diod;

parallel changeBrightning(10); //обновление экрана
parallel lightDiode(20000); //смена цвета диода и дача прогноза
parallel changeLCD(5000); //1 окно
parallel queryToServer(600000); //запрос к серверу
parallel fade(500); //обновление экрана

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
    esp8266Module.postToOurServer();
  }


  if (changeBrightning.isReady() ) {
    gradusnik.changeBrightning();
  }
  if (changeLCD.isReady() && logger == 0 ) {
    led.displayWeather( esp8266Module.getWeatherLocation(),
                        //esp8266Module.getWeatherDescription(),
                        esp8266Module.getBetterRussianDescription( esp8266Module.getWeatherID() ),
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
    //Serial.println( a );
    diod.setColorByRating(a);
  }

//     if (fade.isReady() ) {
//       diod.fading();
//     }
}
