#include "jsonParse.h"
#include <Arduino.h>

#include "output/ArduinoSerialLogging.h"

DynamicJsonDocument parseJSON(String json)  {
    // хз для чего это но пусть будет
    json.replace('[', ' ');
    json.replace(']', ' ');

    DynamicJsonDocument root(1024); //StaticJsonBuffer<1024> json_buf;
    DeserializationError error = deserializeJson(root, json.c_str()); //JsonObject &root = json_buf.parseObject(jsonArray);
    if (error) {
        Fatal() << "Error while parsing json";
    }
    return root;
}
