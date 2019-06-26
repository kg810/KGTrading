#pragma once

#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types>

#include<string>

#include"../../logger/logger.h"

class PipeMgr
{
public:



private:
    static constexpr std::string pipeName;
};

static constexpr PipeMgr::pipeName = "pipeTransport";
