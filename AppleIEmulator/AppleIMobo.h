#pragma once
#include "MotherBoard.h"

class AppleIMobo : public MotherBoard {
    byte memory[65535];

    //Apple I special memory blocks
    byte KBD; //WOZ monitor keyboard input
    byte KBDCR; //WOZ monitor keyboard status
    byte DSP; //WOZ monitor display output
    byte DSPCR; //WOZ monitor display status
    byte statusBits; //status lights on the shift register
    bool statusChanged; //do the bits need to be updated?

    int charsThisLine;
public:
    void initialize() override;
    void writeMemory(byte high, byte low, byte value) override;
    byte readMemory(byte high, byte low) override;
    void iterate() override;
    void copyFileToRam(const char* fileName, byte startHigh, byte startLow);
};