cmake_minimum_required(VERSION 3.4.1)
add_definitions(
    -std=gnu++11
    -fexceptions
    -frtti
    -DUNIX
)

set(TOP_LEVEL ${CMAKE_CURRENT_SOURCE_DIR}/../..)
set(LIB_6502_PATH ${TOP_LEVEL}/lib6502)
set(APPLE_I_EMULATOR_PATH ${TOP_LEVEL}/AppleIEmulator)

add_executable(
    appleIEmulator
    ${LIB_6502_PATH}/src/Common.cpp
    ${LIB_6502_PATH}/src/Core6502.cpp
    ${APPLE_I_EMULATOR_PATH}/src/AppleIEmulator.cpp
    ${APPLE_I_EMULATOR_PATH}/src/AppleIMobo.cpp
    ${APPLE_I_EMULATOR_PATH}/src/conio_unix.cpp
)

target_include_directories (
    appleIEmulator
    PUBLIC ${LIB_6502_PATH}/inc
    PUBLIC ${APPLE_I_EMULATOR_PATH}/inc
)

target_link_libraries(
    appleIEmulator
)