#ifndef HPP_H
#define HPP_H

#include <ArduinoJson.h>
#include "../../output/LCD.hpp"


class http
{
private:
    //LCD led;

public:
    bool postQuery(String host, String path, String requestStr);
    bool getQuery(String host, String path, String requestStr);
    String getResponseFromServer(String result);
    bool countWritenBytes();
    bool checkResponse();
    bool connectToHost(String host);
    bool skipHttpHeaders();

    void checkConnection();
    void debugSerial(String host, String path, String requestStr);
    //void operator << (String sendValue);
    String deleteSpaceForUrlParams(String param);
};

#include "http.cpp"

#endif // HPP_H