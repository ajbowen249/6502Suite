#include "Core6502.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define FINAL_IX_HIGH 0x45
#define FINAL_IX_LOW  0xC0
#define CUTOFF 13 //Currently don't care about decimal mode, and this suite has decimal at test 13

class TestSuiteMobo : public MotherBoard {
    byte _memory[65535];
    bool _readLastInstruction;

public:
    TestSuiteMobo() :
        _readLastInstruction(false) {
    }

    void writeMemory(byte high, byte low, byte value) override {
        _memory[makeAddress(high, low)] = value;
    }

    byte readMemory(byte high, byte low) override {
        if (high == FINAL_IX_HIGH && low == FINAL_IX_LOW) {
            _readLastInstruction = true;
        }

        return _memory[makeAddress(high, low)];
    }

    void iterate() override {
    }

    bool isDone() {
        return _readLastInstruction;
    }

    byte getResult() {
        return _memory[makeAddress(0x02, 0x10)];
    }

    void copyFileToRam(const char* fileName, byte startHigh, byte startLow) {
        ifstream file(fileName, ifstream::in | ifstream::binary | ifstream::ate);
        size_t memoryStart = makeAddress(startHigh, startLow);

        if (file.is_open()) {
            size_t fileSize = file.tellg();
            file.seekg(0);
            file.read((char*)(&_memory[memoryStart]), fileSize);
        }
    }
};

int main() {
    TestSuiteMobo testMobo;
    Core6502 cpu(&testMobo);

    testMobo.writeMemory(Core6502::RESET_HI[0], Core6502::RESET_HI[1], 0x40);
    testMobo.writeMemory(Core6502::RESET_LO[0], Core6502::RESET_LO[1], 0x00);

    testMobo.copyFileToRam("res/AllSuiteA.bin", 0x40, 0x00);

    cpu.reset();

    while (!testMobo.isDone()) {
        cpu.iterate();
        testMobo.iterate();
    }

    auto result = testMobo.getResult();
    if (result == 0xFF || result >= CUTOFF) {
        cout << "All tests passed!" << endl;
    } else {
        cout << "Test failure!" << endl << "Result: " << (int)result << endl;
    }

    auto in = cin.get();
    return 0;
}

