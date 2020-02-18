#ifndef ___PGEN_TERMINAL_H__
#define ___PGEN_TERMINAL_H__

#include "VT100.h"
#include "messages.h"

class Terminal
{
private:
    Stream *stream;
    void printMessage(uint8_t messageId);

public:
    void init(Stream *stream);
    void printBanner();
    void clearScreen();
    void printMasterPasswordPrompt();
    void readMasterPassword(char *masterPassword, byte masterPasswordMaxSize);
};

#endif