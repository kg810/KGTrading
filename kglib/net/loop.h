#pragma once

#include<thread>
#include<assert>

#include "../../logger/logger.h"

class Epoller;

class Loop
{
public:
    void loop();

    void stop();

private:
    std::unique_ptr<Epoller> _poller;
    std::thread _thread;
    bool _looping;
    bool _stop;
    uint64_t _iterations;
};

Loop::Loop()
    : _looping{false},
      _poller(new Epoller(this)),
      _stop(false),
      _iterations(0);
{
    LOG_INFO << "Loop created";
    _poller->init();
}

void Loop::loop()
{
    assert(!_looping);
    _looping = true;

    while(_stop)
    {
        ++_iterations;

        _poller->poll();
    }
}

void Loop::stop()
{
    if(!_stop)
        _stop = true;
}

