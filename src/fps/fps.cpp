/*
 * fps.c
 *
 *  Created on: 2022年4月22日
 *      Author: Legend
 */
//主timer，提供时间基准，维持60fps刷新率


#include "fps.h"
#include "hal_data.h"
#include "buzzer/buzzer.h"

volatile static uint64_t ms_count = 0;
volatile static uint64_t frame_count = 0;
volatile static bool refresh = false;

void g_timer0_1ms_fps_callback(timer_callback_args_t *p_args) {
    if (TIMER_EVENT_CYCLE_END == p_args->event) {
        ms_count++;
        if (ms_count % (1000 / FPS) == 0) {
            frame_count++;
            refresh = true;
            handle_buzzer();
        }
    }
}

uint64_t fps_get_ms() {
    return ms_count;
}

uint64_t fps_get_frame() {
    return frame_count;
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
    R_GPT_Open(&g_timer0_1ms_fps_ctrl, &g_timer0_1ms_fps_cfg);
    R_GPT_Start(&g_timer0_1ms_fps_ctrl);
}
