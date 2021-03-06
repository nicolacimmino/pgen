#ifndef __VAULT_SERVICE_H__
#define __VAULT_SERVICE_H__

#include <Functor.h>
#include <Arduino.h>

class Service
{
private:
    
protected:
    Functor1<byte> reportProgress;
    Functor0 reportCompletion;
    bool running = false;

public:
    Service(const Functor1<byte> &reportProgress, const Functor0 &reportCompletion);
    virtual bool start(byte arg = 0) = 0;
    virtual bool loop() = 0;
    bool isRunning();
};

#endif