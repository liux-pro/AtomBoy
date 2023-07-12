#include "utils.h"
 void setBit(int pos, uint8_t *data, bool bit) {
    if (bit) {
        *data |= (1 << pos);
    } else {
        *data &= ~(1 << pos);
    }
}


 void setBit(uint8_t mask, uint8_t *data, bool bit) {
    if (bit) {
        *data |= mask;
    } else {
        *data &= ~mask;
    }
}

 bool checkBit(uint8_t mask,  const uint8_t *data) {
    return (((*data) & mask) != 0);
}