#pragma once

#include <cstdint>
#include "config.h"

uint8_t *keyScan();

void keyClear();

void keyClear(uint8_t mask);

bool keyCheck(uint8_t mask);
