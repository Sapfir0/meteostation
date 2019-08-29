//
// Created by avdosev on 29.08.2019.
//

#include "Time.h"

#include <ESP8266WiFi.h>

Time::Time() {
    *this = Time::current();
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

Time::Time(int h, int m, int s) {
    this->setHMS(h, m, s);
}

int Time::hour() {
    return (_time/(60*60)+timezone)%24;
}
int Time::minute() {
    return _time/(60)%60;
}
int Time::second() {
    return _time%60;
}

void Time::setHMS(int h, int m, int s) {
    // хз вроде так
    unsigned int seconds_time = (h*360)+(m*60)+s;
    this->_time = seconds_time;
}

void Time::setTimezone(int timezone) {
    this->timezone = timezone;
}