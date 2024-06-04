#pragma once

#include "Core6502.h"
#include "WebMobo.h"

#include <string>

class AppleIWebEmulator {
public:
    AppleIWebEmulator();
    void iterate();
    void onKeyPressed(const std::string& input);

private:
    WebMobo mobo_;
    Core6502 cpu_;
};
