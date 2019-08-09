#ifndef WIFI_H
#define WIFI_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <ctime>

class WIFI {
    private:
        String result;

        //мм свойства
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


    public:
        WIFI();
        void postToOurServer();
        void getWeatherData();
        void getUVindexData();
        void startWifiModule();
        void parseWeatherJSON(String json); //мне не нравится, что это здесь
        void parseUV_JSON(String json);
        float toMmRtSt(float GectoPaskal);

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


        const char * getSSID();
        void setSSID(const char * ssid);
};

#endif // WIFI_H