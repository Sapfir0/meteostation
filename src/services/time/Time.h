//
// Created by avdosev on 29.08.2019.
//

#pragma once

#include <string>
#include <ctime>
#include <cstdint>

class Time {
    private:
        int timezone = 3;
        int dst = 0;
        time_t _time;
    public:
        Time(uint8_t timezone = 0);
        Time(time_t time);

        tm* tmStruct();

        static void updateFromNTP();
        static Time current();
};