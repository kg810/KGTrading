#pragma once

#include<sys/time.h>
#include<sys/epoll.h>
#include<signal.h>
#include<sys/socket.h>

#include<function>
#include<vector>
#include<string>

#include"loop.h"
#include"pipemgr.h"
#include"../../logger/logger.h"

class Epoller
{
public:
    void init()
    {

    }

    void poll()
    (

    )


private:
    std::vector<int> infds;
    std::vector<int> outfds;
    std::vector<std::string> pipes;
    shared_ptr<Loop> _loop;

    std::vector<std::function<void()>> tasks;
};

Epoller::Epoller(Loop* loop)
    :  _loop(loop)
{}
