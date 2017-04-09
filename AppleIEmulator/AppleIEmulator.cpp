// AppleIEmulator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AppleIMobo.h"
#include "Core6502.h"
using namespace std;

int main() {
    AppleIMobo mobo;
    Core6502 cpu(&mobo);

    //set the reset vector to the top of the WOZ monitor program
    mobo.writeMemory(Core6502::RESET_HI[0], Core6502::RESET_HI[1], 0xFF);
    mobo.writeMemory(Core6502::RESET_LO[0], Core6502::RESET_LO[1], 0x00);
    
    mobo.copyFileToRam("programs/binaries/CONSOLETEST.BIN", 0x00, 0x00);
    mobo.copyFileToRam("programs/binaries/WOZMON.BIN", 0xFF, 0x00);
    mobo.copyFileToRam("programs/binaries/A1BASIC.BIN", 0xE0, 0x00);

    cpu.reset();

    while (true) {
        cpu.iterate();
        mobo.iterate();
    }

    return 0;
}
