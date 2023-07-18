#pragma once

#include <cstdint>
#include <cstdlib>

static inline void setBit(uint8_t mask, uint8_t *data, bool bit) {
    if (bit) {
        *data |= mask;
    } else {
        *data &= ~mask;
    }
}

static inline bool checkBit(uint8_t mask,  const uint8_t *data) {
    return (((*data) & mask) != 0);
}

typedef struct { uint64_t state;  uint64_t inc; } pcg32_random_t;

// c语言自带的rand用了malloc,单片机没开动态内存分配的话会挂掉,所以用这个.
uint32_t getRandomNumber();