#ifndef HPP_H
#define HPP_H

#include <ArduinoJson.h>


class http
{
private:
public:
    bool postQuery(String host, String path, String requestStr);
    bool getQuery(String host, String path, String requestStr);
    String getResponseFromServer(String result);
    bool countWritenBytes();
    bool checkResponse();
    bool connectToHost(String host);
    bool skipHttpHeaders();

    void checkConnection();
};

#include "http.cpp"

#endif // HPP_H