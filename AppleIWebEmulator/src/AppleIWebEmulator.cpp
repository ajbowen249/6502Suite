#include "AppleIWebEmulator.h"

#include <emscripten/bind.h>

AppleIWebEmulator::AppleIWebEmulator() :
    mobo_(),
    cpu_(&mobo_) {

    //set the reset vector to the top of the WOZ monitor program
    mobo_.writeMemory(Core6502::RESET_HI[0], Core6502::RESET_HI[1], 0xFF);
    mobo_.writeMemory(Core6502::RESET_LO[0], Core6502::RESET_LO[1], 0x00);

    mobo_.copyFileToRam("programs/binaries/ConsoleCharacterTest.bin", 0x00, 0x00);
    mobo_.copyFileToRam("programs/binaries/WozMonitor.bin", 0xFF, 0x00);
    mobo_.copyFileToRam("programs/binaries/Apple1Basic.bin", 0xE0, 0x00);

    cpu_.reset();
}

void AppleIWebEmulator::iterate() {
    cpu_.iterate();
    mobo_.iterate();
}

void AppleIWebEmulator::onKeyPressed(const std::string& input) {
    auto character = input.at(0);
    mobo_.setChar(character);
}

EMSCRIPTEN_BINDINGS(lib) {
    emscripten::class_<AppleIWebEmulator>("AppleIWebEmulator")
        .constructor<>()
        .function("iterate", &AppleIWebEmulator::iterate)
        .function("onKeyPressed", &AppleIWebEmulator::onKeyPressed);
}
