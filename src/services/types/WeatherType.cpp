#include "WeatherType.h"

#include "../convertors/pressure.h"
#include "../convertors/temperature.h"

#include "sensors/Gradusnik.h"
#include "services/json/jsonParse.h"

#include "output/ArduinoSerialLogging.h"

extern const int meteostationId;
extern Gradusnik gradusnik;

WeatherType::WeatherType(String json) {
    parseWeatherJSON(json);
    inside.humidity = gradusnik.getHumidity();
    inside.temperature = gradusnik.getTemperature();
}

WeatherType::WeatherType() = default;


String WeatherType::deleteSpaceForUrlParams(String param) {
    for(unsigned int i = 0; i < param.length(); i++) {
        if(isspace(param[i])) {
            param[i] = '+';
        }
    }
    return param;
}


String WeatherType::toString() {
    String engDescription = deleteSpaceForUrlParams(outside.weatherDescription);
    String requestStr =
        "temperatureInHome=" + String(inside.temperature)
        + "&humidityInHome=" + String(inside.humidity)
        + "&temperature=" + String(outside.temperature)
        + "&humidity=" + String(outside.humidity)
        + "&pressure=" + String(toMmRtSt(outside.pressure))
        + "&weatherId=" + String(outside.weatherID)
        + "&windSpeed=" + String(outside.windSpeed)
        + "&windDeg=" + String(outside.windDeg)
        + "&icon=" + String(outside.icon)
        + "&engWeatherDescription=" + engDescription
        + "&meteostationId=" + String(meteostationId)
        + "&sunriseTime=" + String(outside.sunriseTime)
        + "&sunsetTime=" + String(outside.sunsetTime)
        ;
        //можно еще передавать основное описание погоды, которое будет доступно по всплывающей подсказке
    //определить как скоро будет дождь
    return requestStr;
}


void WeatherType::parseWeatherJSON(String json) {
    DynamicJsonDocument root = parseJSON(json);
    outside.weatherLocation = root["name"].as<String>();
    outside.country = root["sys"]["country"].as<String>();
    outside.temperature = root["main"]["temp"];
    outside.humidity = root["main"]["humidity"];
    outside.pressure = root["main"]["pressure"];
    outside.windSpeed = root["wind"]["speed"];
    outside.windDeg = root["wind"]["deg"];
    outside.sunriseTime = root["sys"]["sunrise"];
    outside.sunsetTime = root["sys"]["sunset"];

    outside.weatherDescription = (root["weather"]["description"]).as<String>();
    outside.weatherID = (root["weather"]["id"]);
    outside.icon = (root["weather"]["icon"]).as<String>();
    if(!outside.weatherDescription) {  // если хотя бы одно провалилось, то можем дальше не проверять
        Warning() << "Default station isn't exist";
        outside.weatherDescription = (root["weather"]["0"]["description"]).as<String>();
        outside.weatherID = (root["weather"]["0"]["id"]);  // если погода в городе разная, то станций будет много, и нужно получать хотя бы с одной
        outside.icon = (root["weather"]["0"]["icon"]).as<String>();
    }
}

float WeatherType::getPressure(const pressureUnits& mode) {
    switch (mode)  {
        case gPa:
            return outside.pressure;
        case hhMg:
            return toMmRtSt(outside.pressure);
        default:
            return outside.pressure;
    }
}

float WeatherType::getTemperature(const temperatureUnits& mode) {
    switch (mode)  {
        case C:
            return outside.temperature;
        case F:
            return toFarenheit(outside.temperature);
        default:
            return outside.temperature;
    }
}
