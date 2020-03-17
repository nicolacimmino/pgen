#ifndef ___PGEN_TERMINAL_H__
#define ___PGEN_TERMINAL_H__

#include <functor.h>
#include "SafeBuffer.h"
#include "VT100.h"
#include "messages.h"

#define TERMINAL_MAX_HOTKEYS 5
#define TERMINAL_WIDTH 80
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

#define TERMINAL_KEY_ESC 0x1B
#define TERMINAL_KEY_BACKSPACE 0x7F

class Terminal
{
private:
    void printMessage(uint8_t messageId);
    void printHeader();
    void resetInactivityTimer();
    bool checkInactivityTimer();
    int getFreeRamBytes();

    struct terminalHotkey
    {
        Functor0 callback;
        char key;
    };

    Stream *stream;
    terminalHotkey hotkeys[TERMINAL_MAX_HOTKEYS];
    byte lastHotkeyIndex = 0;
    Functor1<byte> menuCallback;
    Functor0 resetCallback;
    uint32_t lastActiveTime;
    bool clpIndicator = false;
    bool lckIndicator = false;
    int keyFingerprint = 0;

public:
    void init(Stream *stream);
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
    void printStatusProgress(char *message, uint32_t delaymS, byte *completedMessage, byte line, byte column, byte areaWidth);
    void print(char *text, byte line = NULL, byte column = NULL);
    void printMenuEntry(byte position, char *text, bool secondLevel = false);
    void printBufferHex(byte *buffer, byte bufferSize);
    void highlightMenuEntry(byte position, bool secondLevel = false);
    bool readString(char *prompt, char *string, byte stringMaxSize, char mask = 0, byte line = NULL, byte column = NULL);
    bool readString(char *prompt, SafeBuffer *string, char mask = 0, byte line = NULL, byte column = NULL);
    byte waitKeySelection(char rangeStart, char rangeEnd);
    void setClpIndicator(bool status);
    void setLclIndicator(bool status);
    void setKeyFingerprint(int keyFingerprint);
    void loop();
};

#endif