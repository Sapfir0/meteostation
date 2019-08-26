
#include <ArduinoJson.h>
#include "output/LCD.h"

bool postQuery(String host, String path, String requestStr);
bool getQuery(String host, String path, String requestStr);
String getResponseFromServer(String result);
bool countWritenBytes();
bool checkResponse();
bool connectToHost(String host);
bool skipHttpHeaders();

void checkConnection();
void debugSerial(String host, String path, String requestStr);

