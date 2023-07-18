#pragma once

#include <cstdint>
#include "config.h"

uint8_t *keyScan();
/**
 * 清空按键标志位
 */
void keyClear(uint8_t mask);
/**
 * 检查并清空按键标志位
 */
bool keyCheck(uint8_t mask);
/**
 * 检查按键标志位
 */
bool keyPeek(uint8_t mask);
/**
 * 等待任意键
 */
void keyWaitAnyKey();