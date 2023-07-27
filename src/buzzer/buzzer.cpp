/*
 * buzzer.cpp
 *
 *  Created on: 2022年5月5日
 *      Author: Legend
 */
/*
 * pwm控制蜂鸣器，使用gpt9(general pwm timer).
 * 瑞萨的gpt0是32位，其他是16位，谨防溢出。
 */
#include "buzzer.h"
#include "fps/fps.h"

static uint64_t stopTime;
static bool on = false;

//开始输出特定频率的pwm，占空比默认50%
void buzzer_start(uint16_t freq, uint16_t lastTime, uint8_t duty) {
    R_GPT_Open(&g_timer9_ctrl, &g_timer9_cfg);
    on = true;
    //设置频率。
    uint32_t pclkd_freq_hz = BSP_STARTUP_PCLKD_HZ >> g_timer9_cfg.source_div;
    auto period_counts = pclkd_freq_hz / freq;
    R_GPT_PeriodSet(&g_timer9_ctrl, (uint32_t) period_counts);
    //设置占空比
    R_GPT_DutyCycleSet(&g_timer9_ctrl, ((uint64_t) period_counts * duty / 256), GPT_IO_PIN_GTIOCA_AND_GTIOCB);
    R_GPT_Reset(&g_timer9_ctrl);
    //开始输出pwm
    R_GPT_Start(&g_timer9_ctrl);

    stopTime = fps_get_ms() + lastTime;
}

void buzzer_stop() {
    R_GPT_Stop(&g_timer9_ctrl);
    R_GPT_Close(&g_timer9_ctrl);
}

void handle_buzzer() {
    if (fps_get_ms() > stopTime and on) {
        on = false;
        buzzer_stop();
    }
}

