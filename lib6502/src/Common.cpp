#include "Common.h"

size_t makeAddress(byte high, byte low) {
    size_t address = 0;
    address |= high;
    address <<= 8;
    address |= low;
    return address;
}
