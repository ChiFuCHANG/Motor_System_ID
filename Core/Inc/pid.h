#ifndef INC_PID_H_
#define INC_PID_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "encoder.h"

typedef struct {
	float Kp;
	float Ki;
	float Kd;
    float err_pre;
    float P_term;
    float I_term;
    float D_term;
    float max_PID;
    float min_PID;
    float max_Integral;
} PID;

float pid_control(PID *pid, float pos, float ref);

#ifdef __cplusplus
}
#endif
#endif /* INC_PID_H_ */
