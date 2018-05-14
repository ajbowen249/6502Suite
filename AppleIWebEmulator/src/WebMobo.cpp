#include "WebMobo.h"

#include <emscripten.h>

#include <fstream>

WebMobo::WebMobo() :
    KBD(0),
    KBDCR(0),
    DSP(0),
    kbHit_(false),
    ch_(' ') { }

WebMobo::~WebMobo() { }

void WebMobo::writeMemory(byte high, byte low, byte value) {
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

byte WebMobo::readMemory(byte high, byte low) {
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

void WebMobo::iterate() {
    if (kbHit()) {
        if ((KBDCR & 0x80) == 0) {
            auto character = ch_;
            if (character >= 'a' && character <= 'z') character -= 32; //Apple I only supports uppercase characters
            KBD = character | 0x80; //make sure the MSB is always high
            KBDCR |= 0x80; //flag the new character
        }
    }

    if (DSP & 0x80) { //write character if needed
        char character = DSP & 0x7F;
        if ((character > 0x1F || character == 0x08 || character == 0x0D) && character != 0x7F) {
            print(character);
        }

        DSP = ~DSP; //flip the bit to show we've written
    }
}

void WebMobo::copyFileToRam(const char* fileName, byte startHigh, byte startLow) {
    std::ifstream file(fileName, std::ifstream::in | std::ifstream::binary | std::ifstream::ate);
    size_t memoryStart = makeAddress(startHigh, startLow);

    if (file.is_open()) {
        size_t fileSize = file.tellg();
        file.seekg(0);
        file.read((char*)(&_memory[memoryStart]), fileSize);
    }
}

EM_JS(void, print_to_screen, (char character), {
    print(character);
});

void WebMobo::print(char character) {
    print_to_screen(character);
}

void WebMobo::setChar(char input) {
    ch_ = input;
    kbHit_ = true;
}

bool WebMobo::kbHit() {
    if (kbHit_) {
        kbHit_ = false;
        return true;
    }

    return false;
}
