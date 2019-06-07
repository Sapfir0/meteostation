#include "../../sensors/gradusnik.hpp"
#include "../translating/rus.hpp"
#include "../json/jsonParse.hpp"
#include "../http/http.hpp"

WIFI::WIFI() {
    // WiFi.begin(_ssid, password);
    // while (WiFi.status() != WL_CONNECTED) {
    //     delay(500);
    //     Serial.println("Connection isnt successful");
    //     //led.loadiiing();  //надо как-то кидать исключение на лсд
    // }
    // Serial.println("Конструктор вифи");
    weatherDescription="unknown";
}

void WIFI::getWeatherData()  { // client function to send/receive GET request data.
    http req;
    connectToServer(CityID, APIKEY);
    result = req.getResponseFromServer(result);
    parsingJSON(result);
}



void WIFI::postToOurServer() {
    int port = 80;
    if (!client.connect(ourServer, port)) { //чет не работет, если сюда переменную кинуть
        Serial.println("connection failed");
        return;
    }
    else {
      Serial.println("connection successful");
    }

    http req;
    Gradusnik grad;
    rus rus;
    String rusDescription = rus.getRussianDescription(getWeatherID() ) ;
    //кодировка русского описания

    rusDescription.trim();

    String engDescription = req.deleteSpaceForUrlParams(engDescription);

    std::time_t result = std::time(nullptr);
    String requestStr = 
        "temperatureInHome=" + String(grad.getTemperature())
        + "&humidityInHome=" + String(grad.getHumidity()) 
        + "&temperature=" + String(getTemperature())
        + "&humidity=" + String(getHumidity())
        + "&pressure=" + String(toMmRtSt(getPressure()))
        + "&rusWeatherDescription=" + rusDescription  
        + "&engWeatherDescription=" + engDescription
        + "&sansity=" + String(grad.getIluminating()) 
        + "&weatherId" + String(getWeatherID())
        + "&windSpreed=" + String(getWindSpeed()) 
        + "&windDeg=" + String(getWindDeg()) 
        + "&icon=" + getIcon()
        //+ "&CURRENTTIMESTAMP=" + String(std::asctime(std::localtime(&result))) //да и эту херню, тут есть перенос в конце
        ;  //можно еще передавать основное описание погоды, которое будет доступно по всплывающей подсказке

//определить как скоро будет дождь

    Serial.println(requestStr);
    req.postQuery(ourServer, "/arduinoData", requestStr);

}


void WIFI::parsingJSON(String json) { //переход на новую версию
    ourJson ourjson;
    DynamicJsonDocument root = ourjson.parseJSON(json);
    setWeatherLocation(root["name"]);
    setCountry(root["sys"]["country"]);
    setTemperature(root["main"]["temp"]);
    setHumidity(root["main"]["humidity"]);
    setPressure(root["main"]["pressure"]);
    setWindSpeed(root["wind"]["speed"]);

    setWeatherDescription(root["weather"]["description"]);
    setWeatherID(root["weather"]["id"]);
    setIcon(root["weather"]["icon"]);
    if(getWeatherDescription() == NULL) { // если хотя бы одно провалилось, то можем дальше не проверять
        Serial.println("Default station isnt exist");
        setWeatherDescription(root["weather"]["0"]["description"]);
        setWeatherID(root["weather"]["0"]["id"]); //если погода в городе разная, то станций будет много, и нужно получать хотя бы с одной
        setIcon(root["weather"]["0"]["icon"]);

    }

}

void WIFI::startWifiModule() {
    WiFi.begin(_ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println("Connection isnt successful");
        //led.loadiiing();  //надо как-то кидать исключение на лсд
    }
    
}

void WIFI::connectToServer(String CityID, String APIKEY) {
    String requestStr = "id=" + CityID +"&units=metric&APPID=" + APIKEY;
    http req;
    req.getQuery("api.openweathermap.org", "/data/2.5/weather", requestStr);
}


float WIFI::toMmRtSt(float GectoPaskal) {
    float res = 0;
    res = GectoPaskal * 100 / 133;
    return res;
}

const char * WIFI::getSSID() {
    return _ssid;
}

String WIFI::getWeatherDescription() {
    return weatherDescription;
}
String WIFI::getWeatherLocation() {
    return weatherLocation;
}
String WIFI::getCountry() {
    return Country;
}
float WIFI::getTemperature() {
    return Temperature;
}
float WIFI::getHumidity() {
    return Humidity;
}
float WIFI::getPressure() {
    return Pressure;
}
int WIFI::getWeatherID() {
    return weatherID;
}
int WIFI::getWindSpeed() {
    return windSpeed;
}

int WIFI::getWindDeg() {
    return windDeg;
}

String WIFI::getIcon() {
    return icon;
}



void WIFI::setSSID(const char * ssid) {
    _ssid = ssid;
}

void WIFI::setWeatherDescription(String weatherDescription) {
    this->weatherDescription = weatherDescription;
}
void WIFI::setWeatherLocation(String weatherLocation) {
    this -> weatherLocation = weatherLocation;
}
void WIFI::setCountry(String country) {
    this->Country = country;
}
void WIFI::setTemperature(float temperature) {
    this->Temperature = temperature;
}
void WIFI::setHumidity(float humidity) {
    this->Humidity = humidity;
}
void WIFI::setPressure(float pressure) {
    this->Pressure = pressure;
}
void WIFI::setWeatherID(int weatherId) {
    this->weatherID = weatherId;
}
void WIFI::setWindSpeed(int windSpeed) {
    this->windSpeed = windSpeed;
}

void WIFI::setWindDeg(int windDeg) {
    this->windDeg = windDeg;
}

void WIFI::setIcon(String icon) {
    this->icon = icon;
}