#include "sleeping.h"

#include <ESP.h>

void deepSleep(unsigned int milliseconds) {
    uint mcSeconds = milliseconds * 1000;
    ESP.deepSleep(mcSeconds);
}