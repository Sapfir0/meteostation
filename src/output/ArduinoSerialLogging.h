//
// Created by avdosev on 05.09.2019.
//

#ifndef METEOSTATION_ARDUINOSERIALLOGGING_H
#define METEOSTATION_ARDUINOSERIALLOGGING_H

#include "services/logger/Logger.h"

extern Logger logs;

#define Debug() logs.Debug
#define Info() logs.Info
#define Warning() logs.Warning
#define Critical() logs.Critical
#define Fatal() logs.Fatal

#endif //METEOSTATION_ARDUINOSERIALLOGGING_H
