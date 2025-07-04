#ifndef __PID_H
#define __PID_H
#include "main.h"


typedef struct
{
  float Kp;
  float Ki;
  float Kd;

  float target;
  float err;
  float lastErr;
  float P_out;
  float I_out;
  float D_out;
  float I_lit;
  float allIit;
  float allOut;
}PID_typedef;
void PID_Init(PID_typedef*PID, const float PID_[3], float max_Iout, float max_allout);
float PID(PID_typedef*PID, float target, float rawvalue);
void PID_clear(PID_typedef*PID);
#endif 
