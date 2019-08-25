#include "jsonParse.h"

#include <Arduino.h>

void ourJson::createJSON()  {

    DynamicJsonDocument doc(1024);
    doc["key"] = "value";
    doc["raw"] = serialized("[1,2,3]");
    serializeJson(doc, Serial);
}

DynamicJsonDocument ourJson::parseJSON(String json)  {
    json.replace('[', ' ');
    json.replace(']', ' ');
    Serial.println(json);
    char jsonArray[json.length() + 1];
    json.toCharArray(jsonArray, sizeof(jsonArray));
    jsonArray[json.length() + 1] = '\0';
    DynamicJsonDocument root(1024); //StaticJsonBuffer<1024> json_buf;
    DeserializationError error = deserializeJson(root, jsonArray); //JsonObject &root = json_buf.parseObject(jsonArray);
    if (error) {
        Serial.println("Error while parsing json");
        //return;
    }
    return root;
}
