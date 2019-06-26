#pragma once

#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

class Logger
{
public:
    enum class LogLevel
    {
        TRACE,
        DEBUG,
        INFO,
        WARN,
        ERROR,
        CRITI,
    };

    Logger()
    {
        el::Configurations cfg("./el.cfg");
        el::Loggers::reconfigureLogger("default", cfg);
        el::Loggers::reconfigureAllLoggers(cfg);
    }

};

