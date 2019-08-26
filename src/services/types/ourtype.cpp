#include "ourtype.h"
#include "../../config.h"

extern const int meteostationId;

Ourtype::Ourtype(String json) {
    Gradusnik grad;
    parseWeatherJSON(json);
    inside.humidity = (grad.getHumidity());
    inside.temperature = (grad.getTemperature());
}

Ourtype::Ourtype() {

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

float Ourtype::toMmRtSt(float GectoPaskal) {
    float res = 0;
    res = GectoPaskal * 100 / 133;
    return res;
}

// void Ourtype::operator=() {

// }

void Ourtype::parseWeatherJSON(String json) { 
    ourJson ourjson;
    DynamicJsonDocument root = ourjson.parseJSON(json);
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
    if(!outside.weatherDescription) { // если хотя бы одно провалилось, то можем дальше не проверять
        Serial.println("Default station isnt exist");
        outside.weatherDescription = (root["weather"]["0"]["description"]).as<String>();
        outside.weatherID = (root["weather"]["0"]["id"]); //если погода в городе разная, то станций будет много, и нужно получать хотя бы с одной
        outside.icon = (root["weather"]["0"]["icon"]).as<String>();
    }
}

