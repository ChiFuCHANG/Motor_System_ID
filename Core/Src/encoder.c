/*
 * encoder.c
 *
 *  Created on: Mar 19, 2025
 *      Author: chifuchang
 */

#ifndef SRC_Encoder_C_
#define SRC_Encoder_C_

#include "encoder.h"

float ENC_pos(Encoder *e, uint16_t cnt)
{
	float pos = e->pre_pos;
    float rad_per_cnt = 2 * M_PI / (float)e->MTR_PPR;
    int16_t delta = cnt - e->pre_cnt;

    // Deal with timer overflow.
    if (delta > (65535 / 2))
    {
        delta -= 65535;
    }
    else if (delta < -(65535 / 2))
    {
        delta += 65535;
    }

    e->pre_cnt = cnt;

    pos += delta * rad_per_cnt;
    return pos;
}

float ENC_vel(Encoder *e, float pos)
{
    float vel = (pos - e->pre_pos) / (float)e->Ts;
    e->pre_pos=  pos;
    return vel;
}

#endif /* SRC_Encoder_C_ */