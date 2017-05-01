cmake  \
    -H. \
    -B. \
    -DEXECUTABLE_OUTPUT_PATH=./build \

cmake --build .

cp -r ../../AppleIEmulator/programs ./build/programs
