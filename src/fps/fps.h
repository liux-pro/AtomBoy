/*
 * fps.h
 *
 *  Created on: 2022年4月22日
 *      Author: Legend
 */

#ifndef TIMER_FPS_H_
#define TIMER_FPS_H_
#include "hal_data.h"
#define FPS 60

void fps_init();
void fps_loop();
//同步控制,sync从0到FPS变化。每次刷新自动增加。
uint8_t fps_get_sync();
//是否需要刷新，这个在主循环里被轮询，
//一旦需要刷新的标志被读取了，自动标记已刷新
bool fps_need_refresh();

#endif /* TIMER_FPS_H_ */
