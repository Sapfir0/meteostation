//
// Created by sapfir on 01.09.2019.
//

#ifndef METEOSTATION_SLEEPING_H
#define METEOSTATION_SLEEPING_H

#include <ESP8266WiFi.h>

void deepSleep(uint milliseconds) {
    uint mcSeconds = pow(milliseconds, 3);
    ESP.deepSleep(mcSeconds);
}

#endif //METEOSTATION_SLEEPING_H
