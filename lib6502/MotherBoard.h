#pragma once
#include "Common.h"

class MotherBoard {
public:
    virtual void writeMemory(byte high, byte low, byte value) = 0;
    virtual byte readMemory(byte high, byte low) = 0;
    virtual void iterate() = 0;
};
