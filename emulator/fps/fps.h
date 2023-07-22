/*
 * fps.h
 *
 *  Created on: 2022年4月22日
 *      Author: Legend
 */

#ifndef TIMER_FPS_H_
#define TIMER_FPS_H_

#include "stdint.h"

#define FPS 60


#ifdef __cplusplus
extern "C" {
#endif
void fps_init();
#ifdef __cplusplus
}
#endif

uint64_t fps_get_ms(); //从启动到现在过去的毫秒数
uint64_t fps_get_frame(); //从启动到现在刷新的帧数
//是否需要刷新，这个在主循环里被轮询，
//一旦需要刷新的标志被读取了，自动标记已刷新
bool fps_need_refresh();

#endif /* TIMER_FPS_H_ */
