/*
 * encoder.h
 *
 *  Created on: Mar 19, 2025
 *      Author: chifuchang
 */

#ifndef INC_ENCODER_H_
#define INC_ENCODER_H_

#include "main.h"

typedef struct{
	float Ts;
	float pre_pos;
	uint16_t MTR_PPR;
	uint16_t pre_cnt;
} Encoder;

float ENC_pos(Encoder *e, uint16_t cnt);
float ENC_vel(Encoder *e, float pos);

#endif /* INC_ENCODER_H_ */
