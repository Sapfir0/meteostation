//
// Created by sapfir on 24.08.2019.
//

#ifndef METEOSTATION_WEATHERTYPE_H
#define METEOSTATION_WEATHERTYPE_H

#include <WString.h>


class WeatherType {
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
        
        WeatherType();
        WeatherType(String json);

        void parseWeatherJSON(String json);
        String toString();
        String deleteSpaceForUrlParams(String param);

        enum pressureUnits {
            gPa,  // гигапаскали
            hhMg  // миллиметры ртутного столба
        };
        enum temperatureUnits {
            C, // celcium
            F // farenheit
        };

        float getPressure(const pressureUnits &mode);
        float getTemperature(const temperatureUnits &mode);

//    private:
        street outside;
        home inside{};


};


#endif //METEOSTATION_WEATHERTYPE_H
