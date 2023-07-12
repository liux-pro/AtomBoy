#pragma once

#include <cstdint>

void setBit(int pos, uint8_t *data, bool bit);

void setBit(uint8_t mask, uint8_t *data, bool bit);

bool checkBit(uint8_t mask, const uint8_t *data);