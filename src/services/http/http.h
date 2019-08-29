
#include <ArduinoJson.h>
#include "output/LCD.h"

String get(String url);

String post(String url, String data);
String request(String method, String url, String data="");