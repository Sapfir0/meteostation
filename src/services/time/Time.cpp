//
// Created by avdosev on 29.08.2019.
//

#include "Time.h"

#include <ESP8266WiFi.h>

Time::Time(uint8_t timezone) : timezone(timezone) {

}

Time::Time(time_t time) : _time(time) {

}

/**
 * update time from ntp server
 */
void Time::updateFromNTP() {
    configTime(0, 0, "pool.ntp.org", "time.nist.gov");
    while (!time(nullptr)) {
        delay(100);
    }
}

Time Time::current() {
    time_t now = time(nullptr);
    return Time(now);
}

tm* Time::tmStruct() {
    return gmtime(&(this->_time));
}