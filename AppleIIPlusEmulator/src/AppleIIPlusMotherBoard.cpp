#include "AppleIIPlusMotherBoard.h"
#include <fstream>

using namespace std;

AppleIIPlusMotherBoard::AppleIIPlusMotherBoard() {

}

void AppleIIPlusMotherBoard::writeMemory(byte high, byte low, byte value) {
    _memory[makeAddress(high, low)] = value;
}

byte AppleIIPlusMotherBoard::readMemory(byte high, byte low) {
    return _memory[makeAddress(high, low)];
}

void AppleIIPlusMotherBoard::iterate() {

}

void AppleIIPlusMotherBoard::copyFileToRam(const char* fileName, byte startHigh, byte startLow) {
    ifstream file(fileName, ifstream::in | ifstream::binary | ifstream::ate);
    size_t memoryStart = makeAddress(startHigh, startLow);

    if (file.is_open()) {
        size_t fileSize = file.tellg();
        file.seekg(0);
        file.read((char*)(&_memory[memoryStart]), fileSize);
    }
}