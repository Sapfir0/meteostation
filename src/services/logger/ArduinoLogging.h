//
// Created by avdosev on 05.09.2019.
//

#ifndef METEOSTATION_ARDUINOLOGGING_H
#define METEOSTATION_ARDUINOLOGGING_H

#include "Logger.h"

extern Logger logs;

#define Debug() logs.Debug
#define Info() logs.Info
#define Warning() logs.Warning
#define Critical() logs.Critical
#define Fatal() logs.Fatal

#endif //METEOSTATION_ARDUINOLOGGING_H
