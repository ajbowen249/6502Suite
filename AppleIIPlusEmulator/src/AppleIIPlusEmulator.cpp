#include "Core6502.h"
#include "AppleIIPlusMotherBoard.h"

int main() {
    AppleIIPlusMotherBoard motherBoard;
    Core6502 cpu(&motherBoard);

    motherBoard.writeMemory(Core6502::RESET_HI[0], Core6502::RESET_HI[1], 0xFF);
    motherBoard.writeMemory(Core6502::RESET_LO[0], Core6502::RESET_LO[1], 0x00);

    motherBoard.copyFileToRam("programs/system/ApplesoftBasic_E000.bin",   0xE0, 0x00);
    motherBoard.copyFileToRam("programs/system/ApplesoftBasic_E800.bin",   0xE8, 0x00);
    motherBoard.copyFileToRam("programs/system/ApplesoftBasic_F000.bin",   0xF0, 0x00);
    motherBoard.copyFileToRam("programs/system/AutostartMonitor_F800.bin", 0xF8, 0x00);

    cpu.reset();

    while (true) {
        cpu.iterate();
        motherBoard.iterate();
    }

    return 0;
}

