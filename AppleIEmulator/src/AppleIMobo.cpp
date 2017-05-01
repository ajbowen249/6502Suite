#include "AppleIMobo.h"
#include <iostream>
#include <fstream>

#ifndef UNIX
    #include <conio.h>
#else
    #include <conio_unix.h>
#endif

using namespace std;

AppleIMobo::AppleIMobo() :
#ifndef UNIX
    _stdOutHandle(GetStdHandle(STD_OUTPUT_HANDLE)),
#endif
    KBD(0),
    KBDCR(0),
    DSP(0),
    charsThisLine(0) {

#ifndef UNIX
    //TODO: Find a way to resize the winow using api-level calls
    system("MODE CON COLS=40 LINES=25");

    SetConsoleTextAttribute(_stdOutHandle, CONSOLE_TEXT_ATTRS);
    
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(_stdOutHandle, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(_stdOutHandle, &cursorInfo);
#else
    cout << "\033[32;40m";
#endif
}

AppleIMobo::~AppleIMobo() {
#ifndef UNIX
    CloseHandle(_stdOutHandle);
#else
    cout << "\033[0m";
#endif
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
            _memory[makeAddress(high, low)] = value;
        }
    } else {
        _memory[makeAddress(high, low)] = value;
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
            return _memory[makeAddress(high, low)];
        }
    } else {
        return _memory[makeAddress(high, low)];
    }
}

void AppleIMobo::iterate() {
    if (_kbhit()) {
        if ((KBDCR & 0x80) == 0) {
            auto character = _getch();
            //WOZ bios uses ascii underscores for backspace and cannot display underscores
            if (character != '_') {
                if (character == 0x08) character = '_';
#ifdef UNIX
                if (character == 0x0A) character = 0x0D;
#endif
                if (character >= 'a' && character <= 'z') character -= 32; //Apple I only supports uppercase characters
                KBD = character | 0x80; //make sure the MSB is always high
                KBDCR |= 0x80; //flag the new character
            }
        }
    }

    if (DSP & 0x80) { //write character if needed
        char character = DSP & 0x7F;
        if (character == 0x0D) {
            charsThisLine = 0;
            printWithCursor('\n');
        } else if ((character > 0x1F || character == 0x08 || character == 0x0D) && character != 0x7F) {
            if (character == '_') character = 0x08;
            printWithCursor(character);
            charsThisLine++;
        }

        DSP = ~DSP; //flip the bit to show we've written

        //if we've gone beyond 40 chararacters, force a line break
        if (charsThisLine >= 40) {
            charsThisLine = 0;
            printWithCursor('\n');
        }
    }
}

void AppleIMobo::copyFileToRam(const char* fileName, byte startHigh, byte startLow) {
    ifstream file(fileName, ifstream::in | ifstream::binary | ifstream::ate);
    size_t memoryStart = makeAddress(startHigh, startLow);

    if (file.is_open()) {
        size_t fileSize = file.tellg();
        file.seekg(0);
        file.read((char*)(&_memory[memoryStart]), fileSize);
    }
}

void AppleIMobo::printWithCursor(char character) {
    if (character == 0x08) {
        cout << ' ';
        cout << character;
    }

    if (character == '\n') {
        cout << ' ';
    }

    cout << character;
    cout << CURSOR_CHAR;

#ifndef UNIX
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(_stdOutHandle, &consoleInfo);

    if (consoleInfo.dwCursorPosition.X > 0) {
        consoleInfo.dwCursorPosition.X--;
        SetConsoleCursorPosition(_stdOutHandle, consoleInfo.dwCursorPosition);
    }
#else
    cout << "\033[1D";
#endif
}
