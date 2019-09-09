//
// Created by avdosev on 04.09.2019.
//

#pragma once

#include <WString.h>

class Logger {
public:
    enum class MsgType {
        DebugMsg,
        InfoMsg,
        WarningMsg,
        CriticalMsg,
        FatalMsg
    };
    using handler_t = void(*)(MsgType, String);
private:
    handler_t messageHandler;

    /**
     * метопрограммная игра
     * */
    template<MsgType msgType>
    class Outputer {
        Logger& toOut;
    public:
        Outputer(Logger& toOut) : toOut(toOut) {}
        Outputer& operator << (String data) {
            toOut.print(msgType, data);
            return *this;
        }
    };
public:
    Outputer<MsgType::DebugMsg> Debug;
    Outputer<MsgType::InfoMsg> Info;
    Outputer<MsgType::WarningMsg> Warning;
    Outputer<MsgType::CriticalMsg> Critical;
    Outputer<MsgType::FatalMsg> Fatal;

    Logger(handler_t msgHandler);

    void setMessageHandler(handler_t newHandler);

    void print(MsgType type, String data);

};

