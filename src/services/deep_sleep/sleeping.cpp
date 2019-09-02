#include "sleeping.h"

#include <Esp.h>

void deepSleep(unsigned int milliseconds) {
    uint mcSeconds = milliseconds * 1000;
    ESP.deepSleep(mcSeconds);
}