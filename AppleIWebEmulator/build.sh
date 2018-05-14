#!/usr/bin/bash

mkdir -p build
cd build

emcc --bind -I../../lib6502/inc/ -I../inc/ ../src/*.cpp ../../lib6502/src/*.cpp --preload-file ../../AppleIEmulator/programs/binaries@/programs/binaries --std=c++11 -s WASM=1 -o lib.js
cp ../www/* .
