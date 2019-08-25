#include "ourtype.h"

Ourtype::Ourtype(String json) {
    Gradusnik grad;
    parseWeatherJSON(json);
    setHumidityInHome(grad.getHumidity());
    setTemperatureInHome(grad.getTemperature());
}

String Ourtype::deleteSpaceForUrlParams(String param) {
    for(uint i=0; i<param.length(); i++) {
        if(isspace(param[i])) {
            param[i] = '+';
        }
    }
    return param;
}

String Ourtype::toString(Ourtype instance) {
    String engDescription = deleteSpaceForUrlParams(getWeatherDescription());

    String requestStr =
        "temperatureInHome=" + String(getTemperatureInHome())
        + "&humidityInHome=" + String(getHumidityInHome())
        + "&temperature=" + String(getTemperature())
        + "&humidity=" + String(getHumidity())
        + "&pressure=" + String(toMmRtSt(getPressure()))
        + "&weatherId=" + String(getWeatherID())
        + "&windSpeed=" + String(getWindSpeed())
        + "&windDeg=" + String(getWindDeg())
        + "&icon=" + String(getIcon())
        + "&engWeatherDescription=" + engDescription
        + "&meteostationId=" + String(meteostationId)
        + "&sunriseTime=" + String(getSunriseTime())
        + "&sunsetTime=" + String(getSunsetTime())
        ;
        //можно еще передавать основное описание погоды, которое будет доступно по всплывающей подсказке
    //определить как скоро будет дождь
    return requestStr;
}

float Ourtype::toMmRtSt(float GectoPaskal) {
    float res = 0;
    res = GectoPaskal * 100 / 133;
    return res;
}

void Ourtype::parseWeatherJSON(String json) { 
    ourJson ourjson;
    DynamicJsonDocument root = ourjson.parseJSON(json);
    setWeatherLocation(root["name"]);
    setCountry(root["sys"]["country"]);
    setTemperature(root["main"]["temp"]);
    setHumidity(root["main"]["humidity"]);
    setPressure(root["main"]["pressure"]);
    setWindSpeed(root["wind"]["speed"]);
    setWindDeg(root["wind"]["deg"]);
    setSunriseTime(root["sys"]["sunrise"]);
    setSunsetTime(root["sys"]["sunset"]);

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


String Ourtype::getWeatherDescription() {
    return weatherDescription;
}
String Ourtype::getWeatherLocation() {
    return weatherLocation;
}
String Ourtype::getCountry() {
    return Country;
}
float Ourtype::getTemperature() {
    return Temperature;
}
float Ourtype::getHumidity() {
    return Humidity;
}
float Ourtype::getPressure() {
    return Pressure;
}
int Ourtype::getWeatherID() {
    return weatherID;
}
int Ourtype::getWindSpeed() {
    return windSpeed;
}
int Ourtype::getWindDeg() {
    return windDeg;
}
String Ourtype::getIcon() {
    return icon;
}
long Ourtype::getSunsetTime() {
    return sunsetTime;
}
long Ourtype::getSunriseTime() {
    return sunriseTime;
}
double Ourtype::getTemperatureInHome() {
    return temperatureInHome;
}
double Ourtype::getHumidityInHome() {
    return humidityInHome;
}

void Ourtype::setWeatherDescription(String weatherDescription) {
    this->weatherDescription = weatherDescription;
}
void Ourtype::setWeatherLocation(String weatherLocation) {
    this -> weatherLocation = weatherLocation;
}
void Ourtype::setCountry(String country) {
    this->Country = country;
}
void Ourtype::setTemperature(float temperature) {
    this->Temperature = temperature;
}
void Ourtype::setHumidity(float humidity) {
    this->Humidity = humidity;
}
void Ourtype::setPressure(float pressure) {
    this->Pressure = pressure;
}
void Ourtype::setWeatherID(int weatherId) {
    this->weatherID = weatherId;
}
void Ourtype::setWindSpeed(int windSpeed) {
    this->windSpeed = windSpeed;
}
void Ourtype::setWindDeg(int windDeg) {
    this->windDeg = windDeg;
}
void Ourtype::setIcon(String icon) {
    this->icon = icon;
}
void Ourtype::setSunsetTime(long sunsetTime) {
    this->sunsetTime = sunsetTime;
}
void Ourtype::setSunriseTime(long sunriseTime) {
    this->sunriseTime = sunriseTime;
}
void Ourtype::setTemperatureInHome(double temperatureInHome) {
    this->temperatureInHome = temperatureInHome;
}
void Ourtype::setHumidityInHome(double humidityInHome) {
    this->humidityInHome = humidityInHome;
}