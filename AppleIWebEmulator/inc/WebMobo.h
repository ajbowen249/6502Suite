#pragma once
#include "MotherBoard.h"

class WebMobo : public MotherBoard {
public:
    WebMobo();
    ~WebMobo();
    void writeMemory(byte high, byte low, byte value) override;
    byte readMemory(byte high, byte low) override;
    void iterate() override;
    void copyFileToRam(const char* fileName, byte startHigh, byte startLow);
    void setChar(char input);
    bool kbHit();

private:
    byte _memory[65535];

    //Apple I special memory blocks
    byte KBD; //WOZ monitor keyboard input
    byte KBDCR; //WOZ monitor keyboard status
    byte DSP; //WOZ monitor display output
    byte DSPCR; //WOZ monitor display status

    bool kbHit_;
    char ch_;

    void print(char chacter);
};
