//
// Created by sapfir on 24.08.2019.
//

#ifndef METEOSTATION_OURTYPE_H
#define METEOSTATION_OURTYPE_H
#include <Arduino.h>
#include <ArduinoJson.h>
#include "../sensors/gradusnik.hpp"
#include "../services/json/jsonParse.hpp"

class Ourtype {
    public:
        Ourtype(String json);

        void parseWeatherJSON(String json);
        String toString(Ourtype instance);
        float toMmRtSt(float GectoPaskal);
        String deleteSpaceForUrlParams(String param);

        String getWeatherDescription();
        String getWeatherLocation();
        String getCountry();
        float getTemperature();
        float getHumidity();
        float getPressure();
        int getWeatherID();
        int getWindSpeed();
        String getIcon();
        double getUVindex();
        int getWindDeg();
        long getSunsetTime();
        long getSunriseTime();
        double getTemperatureInHome();
        double getHumidityInHome();

        void setWeatherDescription(String weatherDescription);
        void setWeatherLocation(String weatherLocation);
        void setCountry(String country);
        void setTemperature(float temperature);
        void setHumidity(float humidity);
        void setPressure(float pressure);
        void setWeatherID(int weatherID);
        void setWindSpeed(int windSpeed);
        void setIcon(String icon);
        void setWindDeg(int windDeg);
        void setUVindex(double uvindex);
        void setSunsetTime(long sunsetTime);
        void setSunriseTime(long sunriseTime);
        void setTemperatureInHome(double temperatureInHome);
        void setHumidityInHome(double humidityInHome);

    private:
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
} 


#endif //METEOSTATION_OURTYPE_H
