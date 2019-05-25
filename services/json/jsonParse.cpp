
void createJSON()  {

    DynamicJsonDocument doc(1024);
    doc["key"] = "value";
    doc["raw"] = serialized("[1,2,3]");
    serializeJson(doc, Serial);
}

void parseJSON()  {

    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, json);
    if (error)
        return;
    int value = doc["value"];
}