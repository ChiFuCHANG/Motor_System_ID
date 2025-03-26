/*
 * motor.h
 *
 *  Created on: Mar 19, 2025
 *      Author: chifuchang
 */

#ifndef INC_MOTOR_H_
#define INC_MOTOR_H_

#include "main.h"

void mtr_init(void);


float mtr_input(float t);

float mtr_duty(float u);

void mtr_output(float duty_cyle);

#endif /* INC_MOTOR_H_ */
