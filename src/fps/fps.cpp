/*
 * fps.c
 *
 *  Created on: 2022年4月22日
 *      Author: Legend
 */
//主timer，提供时间基准，维持60fps刷新率


#include "fps.h"
#include "debug/debug.h"


volatile int8_t sync = 0;

volatile bool refresh = false;

void gpt0_fps_callback(timer_callback_args_t *p_args) {
	if (TIMER_EVENT_CYCLE_END == p_args->event) {
		sync = (++sync) % (FPS);
		refresh = true;
	}
}
//同步控制,sync从0到FPS变化。每次刷新自动增加。
uint8_t fps_get_sync() {
	return sync % FPS;
}

//是否需要刷新，这个在主循环里被轮询，一旦需要刷新的标志被读取了，自动标记已刷新
bool fps_need_refresh() {
	if (refresh) {
		//自动标记已刷新
		refresh = false;
		return true;
	};
	return false;
}

void fps_init() {
	R_GPT_Open(&gpt0_fps_ctrl, &gpt0_fps_cfg);
	R_GPT_Start(&gpt0_fps_ctrl);
}
