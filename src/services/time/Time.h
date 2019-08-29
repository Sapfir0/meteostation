//
// Created by avdosev on 29.08.2019.
//

#pragma once

#include <string>
#include <ctime>
#include <cstdint>

class Time {
    private:
        int timezone = 0;
        time_t _time;
    public:
        Time();
        Time(time_t time);
        Time(int h, int m, int s);

        int hour();
        int minute();
        int second();

        void setHMS(int h, int m, int s);

        void setTimezone(int timezone);

        tm* tmStruct();

        static void updateFromNTP();

        static Time current();
};