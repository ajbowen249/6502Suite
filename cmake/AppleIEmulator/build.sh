cmake  \
    -H. \
    -B. \
    -DEXECUTABLE_OUTPUT_PATH=./out \

cmake --build .

cp -r ../../AppleIEmulator/programs ./out/programs
