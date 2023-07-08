#pragma once
#include "hal_data.h"
#include "u8g2_port.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ARRAY_LENGTH(arr) (sizeof(arr) / sizeof(arr[0]))

#define delay(ms) R_BSP_SoftwareDelay(ms, BSP_DELAY_UNITS_MILLISECONDS)

void setup();
void loop();

