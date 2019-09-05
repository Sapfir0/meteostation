//
// Created by avdosev on 05.09.2019.
//

#include "ArduinoLogging.h"

#include <Arduino.h>

void arduinoOutput(Logger::MsgType msgType, String msg) {
    switch (msgType) {
        case Logger::MsgType::DebugMsg:
            Serial.print("");
            break;
        case Logger::MsgType::InfoMsg:
            Serial.print("");
            break;
        case Logger::MsgType::WarningMsg:
            Serial.print("Warning: ");
            break;
        case Logger::MsgType::CriticalMsg:
            Serial.print("Critical: ");
            break;
        case Logger::MsgType::FatalMsg:
            Serial.print("Fatal: ");
            break;
    }
    Serial.println(msg);
}

Logger logs(arduinoOutput);