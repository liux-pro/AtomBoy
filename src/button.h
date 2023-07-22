#pragma once

#include <cstdint>
#include "config.h"

uint16_t *keyScan();
/**
 * 清空按键标志位
 */
void keyClear(uint16_t mask);
/**
 * 检查并清空按键标志位
 */
bool keyCheck(uint16_t mask);
/**
 * 检查按键标志位
 */
bool keyPeek(uint16_t mask);
/**
 * 等待任意键
 */
void keyWaitAnyKey();