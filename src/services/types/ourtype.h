//
// Created by sapfir on 24.08.2019.
//

#ifndef METEOSTATION_OURTYPE_H
#define METEOSTATION_OURTYPE_H
#include <Arduino.h>
#include <ArduinoJson.h>
#include "../../sensors/gradusnik.h"
#include "../../services/json/jsonParse.h"

class Ourtype {
    public:
        struct home  {   
            float humidity;
            float temperature;
        };

        struct street  {
            String weatherDescription;
            String weatherLocation;
            String country;
            float temperature;
            float humidity;
            float pressure;
            int weatherID;
            int windSpeed;
            String icon;
            int windDeg;
            long sunsetTime;
            long sunriseTime;
            double uvindex;
                
        };
        
        Ourtype();
        Ourtype(String json);

        void parseWeatherJSON(String json);
        String toString(Ourtype instance);
        String deleteSpaceForUrlParams(String param);

        enum pressureUnits {
            gPa,  // гигапаскали
            hhMg  // миллиметры ртутного столба
        };
        enum temperatureUnits {
            C, // celcium
            F // farenheit
        };

        float getPressure(pressureUnits mode);
        float getTemperature(temperatureUnits mode);
//    private:
        street outside;
        home inside;

};


#endif //METEOSTATION_OURTYPE_H
