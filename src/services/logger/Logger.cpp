//
// Created by avdosev on 04.09.2019.
//

#include "Logger.h"

Logger::Logger(handler_t msgHandler) : messageHandler(msgHandler),
Debug(*this), Info(*this), Warning(*this), Critical(*this), Fatal(*this)
{

}

void Logger::setMessageHandler(Logger::handler_t newHandler) {
    this->messageHandler = newHandler;
}

void Logger::print(MsgType type, String data) {
    messageHandler(type, data);
}