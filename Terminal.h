#ifndef ___PGEN_TERMINAL_H__
#define ___PGEN_TERMINAL_H__

#include <Functor.h>
#include "VT100.h"
#include "messages.h"
#include "NoiseSource.h"
#include "EncryptedStore.h"

#define TERMINAL_SERIAL_SPEED 9600
#define TERMINAL_MAX_HOTKEYS 5
#define TERMINAL_WIDTH 80
#define TERMINAL_ALERT_WIDTH 50
#define TERMINAL_HEIGTH 24
#define TERMINAL_FIRST_CANVAS_LINE 10
#define TERMINAL_CANVAS_LINES 12
#define TERMINAL_STATUS_LINE 23
#define TERMINAL_HEADER_LINE 1
#define TERMINAL_BANNER_LINE 2
#define TERMINAL_RIGHT_HALF_FIRST_COLUMN (TERMINAL_WIDTH / 2) - 3
#define TERMINAL_BACKGROUND_COLOR VT_BLACK
#define TERMINAL_FOREGROUND_COLOR VT_YELLOW
#define TERMINAL_LABEL_COLOR VT_WHITE
#define TERMINAL_STATUS_LINE_BACKGROUND_COLOR VT_YELLOW
#define TERMINAL_STATUS_LINE_FOREGROUND_COLOR VT_BLACK
#define TERMINAL_MENU_BASE 100
#define TERMINAL_MAX_INACTIVE_TIME_MS 60000
#define TERMINAL_OPERATION_ABORTED 255
#define MENU_L1_FIRST_POS 0
#define MENU_L2_FIRST_POS TERMINAL_CANVAS_LINES
#define TERMINAL_LEFT_MENU_FIRST_COLUMN 5
#define TERMINAL_RIGHT_MENU_FIRST_COLUMN TERMINAL_RIGHT_HALF_FIRST_COLUMN
#define TEMRINAL_KEY_FINGERPRINT_DISPLAY_TIMEOUT 1000
#define TERMINAL_MENU_MAX_ENTRIES 16 

#define TERMINAL_KEY_ESC 0x1B
#define TERMINAL_KEY_BACKSPACE 0x7F
#define TERMINAL_XON 0x11
#define TERMINAL_XOFF 0x13

class Terminal
{
private:
    void printMessage(uint8_t messageId);
    void printHeader();    
    bool checkInactivityTimer();
    int getFreeRamBytes();    
    byte maxMenuPosition = 0;
    unsigned long showKeyFingerprintUntil=0;
    EncryptedStore *encryptedStore;

    struct terminalHotkey
    {
        Functor0 callback;
        char key;
    };

    Stream *stream;
    terminalHotkey hotkeys[TERMINAL_MAX_HOTKEYS];    
    Functor0 menuCallbacks[TERMINAL_MENU_MAX_ENTRIES];
    byte lastHotkeyIndex = 0;
    Functor1<byte> menuCallback;
    Functor0 resetCallback;
    uint32_t lastActiveTime;    
    
public:
    Terminal(EncryptedStore *enctryptedStore);
    void init();
    void clearHotkeys();
    void clearInputBuffer();
    void addHotkey(char key, const Functor0 &action);
    void setMenuCallback(const Functor1<byte> &menuCallback);
    void setResetCallback(const Functor0 &resetCallback);
    void clearScreen();
    void clearCanvas();
    void printBanner();
    void printHeaderMessage(char *message);
    void printStatusMessage(char *message);    
    void print(char *text, byte line = NULL, byte column = NULL);
    void printMenuEntry(byte position, char *text, char *selectorColor = VT_FOREGROUND_WHITE, Functor0 callback = NULL);    
    void highlightMenuEntry(byte position);
    bool askQuestion(char *prompt, char *string, byte stringMaxSize, char mask = 0, byte line = NULL, byte column = NULL, bool noTimeout = false);
    char waitKeySelection();
    bool askYesNoQuestion(char *question, bool warning = false);        
    void alert(char *message, bool warning = false);
    void showProgress(byte progressPercentile);
    void showKeyFingerprint();
    void flowControl(bool on);
    void readLine(char *line, byte bufferSize);
    void loop(bool noTerminalInput = false);
    bool clientRequestedAbort();
    void resetInactivityTimer();
    void flushInput();
};

#endif