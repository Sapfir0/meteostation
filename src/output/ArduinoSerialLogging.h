//
// Created by avdosev on 05.09.2019.
//

#pragma once

#include "services/logger/Logger.h"

extern Logger logs;

#define Debug() logs.Debug
#define Info() logs.Info
#define Warning() logs.Warning
#define Critical() logs.Critical
#define Fatal() logs.Fatal