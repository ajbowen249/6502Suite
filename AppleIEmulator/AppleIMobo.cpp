#include "AppleIMobo.h"
#include <iostream>
#include <conio.h>
#include <fstream>

using namespace std;

void AppleIMobo::initialize() {
    charsThisLine = 0;
}

void AppleIMobo::writeMemory(byte high, byte low, byte value) {
    if (high == 0xD0) {
        if (low == 0x10) {
            KBD = value;
        } else if (low == 0x11) { 
            KBDCR = value; 
        } else if (low == 0x12) {
            DSP = value | 0x80;
        } else if (low == 0x13) {
            DSPCR = value;
        } else {
            memory[makeAddress(high, low)] = value;
        }
    } else { 
        memory[makeAddress(high, low)] = value;
    }
}

byte AppleIMobo::readMemory(byte high, byte low) {
    if (high == 0xD0) {
        if (low == 0x10) {
            KBDCR |= 0x80;
            KBDCR ^= 0x80;
            return KBD;
        } else if (low == 0x11) {
            return KBDCR;
        } else if (low == 0x12) {
            return DSP;
        } else if (low == 0x13) {
            return DSPCR;
        } else {
            return memory[makeAddress(high, low)];
        }
    } else {
        return memory[makeAddress(high, low)];
    }
}

void AppleIMobo::iterate() {
    if (_kbhit()) {
        if ((KBDCR & 0x80) == 0) {
            KBD = _getch() | 0x80; //make sure the MSB is always high
            KBDCR |= 0x80; //flag the new character
        }
    }

    if (DSP & 0x80) { //write character if needed
        char character = DSP & 0x7F;
        if (character > 0x1F || character == 0x08 || character == 0x0D) {
            cout << character;
            charsThisLine++;

            if (character == 0x0D) {
                charsThisLine = 0;
                cout << endl;
            }
        }

        DSP = ~DSP; //flip the bit to show we've written

        //if we've gone beyond 40 chararacters, force a line break
        if (charsThisLine >= 40) {
            charsThisLine = 0;
            cout << endl;
        }
    }
}

void AppleIMobo::copyFileToRam(const char* fileName, byte startHigh, byte startLow) {
    ifstream file(fileName, ifstream::in | ifstream::binary | ifstream::ate);
    size_t memoryStart = makeAddress(startHigh, startLow);

    if (file.is_open()) {
        size_t fileSize = file.tellg();
        file.seekg(0);
        file.read((char*)(&memory[memoryStart]), fileSize);
    }
}