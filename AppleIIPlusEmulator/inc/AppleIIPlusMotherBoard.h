#include "MotherBoard.h"

class AppleIIPlusMotherBoard : public MotherBoard {
    byte _memory[65535];

public:
    AppleIIPlusMotherBoard();
    void writeMemory(byte high, byte low, byte value) override;
    byte readMemory(byte high, byte low) override;
    void iterate() override;
    void copyFileToRam(const char* fileName, byte startHigh, byte startLow);
};
