/*
 * buzzer.h
 *
 *  Created on: 2022年5月5日
 *      Author: Legend
 */

#ifndef BUZZER_BUZZER_H_
#define BUZZER_BUZZER_H_

#include "hal_data.h"


/**
 * 输出pwm信号
 * @param freq 频率 hz
 * @param lastTime 持续时间 毫秒
 * @param duty 占空比(当音量用)
 */
void buzzer_start(uint16_t freq, uint16_t lastTime, uint8_t duty = 128);

/**
 * 停止pwm
 */
void buzzer_stop();

void handle_buzzer();

#endif /* BUZZER_BUZZER_H_ */
