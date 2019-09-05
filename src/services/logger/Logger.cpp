//
// Created by avdosev on 04.09.2019.
//

#include "Logger.h"

void Logger::setMessageHandler(Logger::handler_t newHandler) {
    this->messageHandler = newHandler;
}