//
// Created by sapfir on 24.08.2019.
//

#ifndef METEOSTATION_OURTYPE_H
#define METEOSTATION_OURTYPE_H
#include <Arduino.h>
#include <ArduinoJson.h>
#include "../sensors/gradusnik.h"
#include "../services/json/jsonParse.h"

class Ourtype {
    public:
        Ourtype();
        Ourtype(String json);

        void parseWeatherJSON(String json);
        String toString(Ourtype instance);
        float toMmRtSt(float GectoPaskal);
        String deleteSpaceForUrlParams(String param);


        String weatherDescription = "";
        String weatherLocation = "";
        String Country;
        float Temperature;
        float Humidity;
        float Pressure;
        int weatherID;
        int windSpeed;
        String icon;
        int windDeg;
        double uvindex;
        long sunsetTime;
        long sunriseTime;

        double humidityInHome;
        double temperatureInHome;
};


#endif //METEOSTATION_OURTYPE_H
