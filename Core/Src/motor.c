/*
 * motor.c
 *
 *  Created on: Mar 19, 2025
 *      Author: chifuchang
 */

#include <motor.h>

#define AMPLITUDE MTR_MAX
#define TIME_PERIOD M_PI_2
#define OFFSET 0.0
#define F0 0.5   // 起始頻率 (Hz)
#define F1 50.0  // 終止頻率 (Hz)
#define T 5.0    // 掃頻時間 (秒)
#define PHI0 M_PI_2

void mtr_init(void)
{
	TIM2->CCR1 = 0;
	HAL_GPIO_WritePin(MTR_CW_GPIO_Port, MTR_CW_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(MTR_CCW_GPIO_Port, MTR_CCW_Pin, GPIO_PIN_RESET);
}

static inline float sine_wave(float t)
{
	float output;
	output = AMPLITUDE * sinf(2 * M_PI * t / TIME_PERIOD) + OFFSET;
	return output;
}

static inline float chirp_signal(float t) {
	float output;
	float c = (F1 - F0) / T;
	float time_T = 0.5 * t;
	output = AMPLITUDE * cosf(PHI0 + 2 * M_PI * ((c / 2) * time_T * time_T + F0 * time_T));
	return output;
}

float mtr_input(float t)
{
//	return sine_wave(t);
	return chirp_signal(t);
}

float mtr_duty(float u)
{
	if (u > MTR_MAX) return MAX_DUTY;
	else if (u < MTR_MIN) return MIN_DUTY;
	else return (u / MTR_MAX);
}

void mtr_output(float duty_cycle)
{
	bool dir = duty_cycle > 0.;
	float pwm_val = (float)PWM_ARR * fabs(duty_cycle);
	/* PWM */
	if (pwm_val < 500) pwm_val = 450;	 // Avoid the motor dead zone.
	TIM2->CCR1 = pwm_val;
	HAL_GPIO_WritePin(MTR_CW_GPIO_Port, MTR_CW_Pin, !dir);
	HAL_GPIO_WritePin(MTR_CCW_GPIO_Port, MTR_CCW_Pin, dir);
}
