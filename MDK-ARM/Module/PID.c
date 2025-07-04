#include "PID.h"


#define square(x) ((x) * (x))

#define LimitMax(input, max)       \
    {                              \
        if (input > max) {         \
            input = max;           \
        } else if (input < -max) { \
            input = -max;          \
        }                          \
    }

/**
 * @brief PID�ṹ���ʼ��
 *
 * @param PID PID�ṹ��ָ��
 * @param PID PID������kp��ki��kd��
 * @param max_Iout �������޷�
 * @param max_allout ������޷�
 */
void PID_Init( PID_typedef *PID, const float PID_[3], float max_Iout, float max_allout)
{
    if (PID == NULL || PID_ == NULL) {
        return;
    }
    PID->Kp     = PID_[0];
    PID->Ki     = PID_[1];
    PID->Kd     = PID_[2];
    PID->I_lit  = max_Iout;
    PID->allIit = max_allout;
    PID->err = PID->lastErr = 0;
}
/**
 * @brief PID����
 *
 * @param PID PID�ṹ��ָ��
 * @param target Ŀ��ֵ
 * @param rawvalue ��������ʵֵ
 * @return float PID���
 */
float PID( PID_typedef *PID, float target, float rawvalue)
{
    if (PID == NULL) {
        return 0.0f;
    }
	PID->target  = target;
    PID->lastErr = PID->err;
    PID->err     = target - rawvalue;
    PID->P_out   = PID->Kp * PID->err;
    PID->I_out += PID->Ki * PID->err;
    PID->D_out = PID->Kd * (PID->err - PID->lastErr);
    LimitMax(PID->I_out, PID->I_lit);
    PID->allOut = PID->P_out + PID->I_out + PID->D_out;
    LimitMax(PID->allOut, PID->allIit);
    return PID->allOut;
}

/**
 * @brief PID��պ���
 *
 * @param PID PID�ṹ��ָ��
 */
void PID_clear( PID_typedef *PID)
{
    if (PID == NULL) {
        return;
    }
    PID->err = PID->lastErr = 0;
    PID->P_out = PID->I_out = PID->D_out = PID->allOut = 0;
}
