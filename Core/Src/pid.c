#include "pid.h"

float pid_control(PID *pid, float pos, float ref)
{
	float output;
	pid->P_term = ref - pos;
	pid->I_term += pid->P_term;
	if (pid->I_term >= pid->max_Integral)
	{
		pid->I_term = pid->max_Integral;
	}
	else if (pid->I_term <= pid->max_Integral)
	{
		pid->I_term = -pid->max_Integral;
	}
	pid->D_term = pid->P_term - pid->err_pre;
	pid->err_pre = pid->P_term;
	output = pid->Kp * pid->P_term + pid->Ki * pid->I_term + pid->Kd * pid->D_term;
	return output;
}
