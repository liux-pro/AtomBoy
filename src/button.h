#pragma once

#include <cstdint>
#define KEY_POWER      ((uint16_t)(1 << 0))
#define KEY_A          ((uint16_t)(1 << 1))
#define KEY_A_UP       ((uint16_t)(1 << 2))
#define KEY_A_DOWN     ((uint16_t)(1 << 3))
#define KEY_A_LEFT     ((uint16_t)(1 << 4))
#define KEY_A_RIGHT    ((uint16_t)(1 << 5))
#define KEY_B          ((uint16_t)(1 << 6))
#define KEY_B_UP       ((uint16_t)(1 << 7))
#define KEY_B_DOWN     ((uint16_t)(1 << 8))
#define KEY_B_LEFT     ((uint16_t)(1 << 9))
#define KEY_B_RIGHT    ((uint16_t)(1 << 10))
#define KEY_ANY        ((uint16_t)(0xFFFFFFFF))

/**
 * 扫描按键,当前按键状态.
 * 这个状态指的是当前实际状态.直接表示按键在这个时刻是否被按下或抬起
 * @return
 */
uint16_t keyScan();
/**
 * 清空按键标志位
 */
void keyClear(uint16_t mask);
/**
 * 检查并清空按键标志位
 * 按下的一瞬间会被置位,与是否抬起无关
 */
bool keyCheck(uint16_t mask);
/**
 * 检查按键标志位
 * 按下的一瞬间会被置位,与是否抬起无关
 */
bool keyPeek(uint16_t mask);
/**
 * 等待任意键
 */
void keyWaitAnyKey();