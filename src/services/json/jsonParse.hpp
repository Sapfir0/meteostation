#ifndef JSON_H
#define JSON_H

#include <ArduinoJson.h>

class ourJson
{
    private:

    public:
        void createJSON();
        DynamicJsonDocument parseJSON(String json);
        //DynamicJsonDocument setJSON();

};

#endif // JSON_H