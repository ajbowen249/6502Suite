#pragma once
#include "MotherBoard.h"

#ifndef UNIX
    #include <Windows.h>
#endif

#define CURSOR_CHAR '@'
#define CONSOLE_TEXT_ATTRS FOREGROUND_GREEN | FOREGROUND_INTENSITY

class AppleIMobo : public MotherBoard {
#ifndef UNIX
    HANDLE _stdOutHandle;
#endif

    byte _memory[65535];

    //Apple I special memory blocks
    byte KBD; //WOZ monitor keyboard input
    byte KBDCR; //WOZ monitor keyboard status
    byte DSP; //WOZ monitor display output
    byte DSPCR; //WOZ monitor display status

    int charsThisLine;
    void printWithCursor(char chacter);
public:
    AppleIMobo();
    ~AppleIMobo();
    void writeMemory(byte high, byte low, byte value) override;
    byte readMemory(byte high, byte low) override;
    void iterate() override;
    void copyFileToRam(const char* fileName, byte startHigh, byte startLow);
};