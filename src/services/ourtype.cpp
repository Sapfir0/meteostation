#include "ourtype.h"
#include "../../config.h"

extern const int meteostationId;

Ourtype::Ourtype(String json) {
    Gradusnik grad;
    parseWeatherJSON(json);
    humidityInHome = (grad.getHumidity());
    temperatureInHome = (grad.getTemperature());
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
    String engDescription = deleteSpaceForUrlParams(weatherDescription);

    String requestStr =
        "temperatureInHome=" + String(temperatureInHome)
        + "&humidityInHome=" + String(humidityInHome)
        + "&temperature=" + String(Temperature)
        + "&humidity=" + String(Humidity)
        + "&pressure=" + String(toMmRtSt(Pressure))
        + "&weatherId=" + String(weatherID)
        + "&windSpeed=" + String(windSpeed)
        + "&windDeg=" + String(windDeg)
        + "&icon=" + String(icon)
        + "&engWeatherDescription=" + engDescription
        + "&meteostationId=" + String(meteostationId)
        + "&sunriseTime=" + String(sunriseTime)
        + "&sunsetTime=" + String(sunsetTime)
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
    weatherLocation = root["name"].as<String>();
    Country = root["sys"]["country"].as<String>();
    Temperature = (root["main"]["temp"]);
    Humidity = (root["main"]["humidity"]);
    Pressure = (root["main"]["pressure"]);
    windSpeed = (root["wind"]["speed"]);
    windDeg = root["wind"]["deg"];
    sunriseTime = (root["sys"]["sunrise"]);
    sunsetTime = (root["sys"]["sunset"]);

    weatherDescription = (root["weather"]["description"]).as<String>();
    weatherID = (root["weather"]["id"]);
    icon = (root["weather"]["icon"]).as<String>();
    if(!weatherDescription) { // если хотя бы одно провалилось, то можем дальше не проверять
        Serial.println("Default station isnt exist");
        weatherDescription = (root["weather"]["0"]["description"]).as<String>();
        weatherID = (root["weather"]["0"]["id"]); //если погода в городе разная, то станций будет много, и нужно получать хотя бы с одной
        icon = (root["weather"]["0"]["icon"]).as<String>();
    }
}

