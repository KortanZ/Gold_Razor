#ifndef _PID_H_
#define _PID_H_

typedef struct{
	float32 Kp = 0;
	float32 Kd = 0;
	float32 Ki = 0;
	float32 error[3] = {0,};
}PIDStruct;

#endif	