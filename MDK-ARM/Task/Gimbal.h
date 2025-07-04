#ifndef __GIMBAL_H
#define __GIMBAL_H

#include "Motor.h"
#include "_CAN.h"
#include "PID.h"
#include "_USART.h"
#include "Vofa.h"
#include "Gyroscope.h"
#include "freertos.h"
#include "cmsis_os.h"

#define Pitch_Upper_Limit  3585
#define Pitch_Lower_Limit 1800
#define PitchInit_Angle   2500

#define Yaw_Upper_Limit 8000
#define Yaw_Lower_Limit 1800
#define YawInit_Angle   3000



#define Gyro_Pitch_Upper_Limit 10
#define Gyro_Pitch_Lower_Limit -30

#define Gyro_PitchInit_Angle   0

#define Gyro_Yaw_Upper_Limit 75
#define Gyro_Yaw_Lower_Limit -75
#define Gyro_YawInit_Angle   0



//enum GimbalState
//{
//  // ��ֹ̨ͣ״̬
//  GimbalStateStop = 0,
//  // ��̨��ң��״̬
//  GimbalStateRemote,
//  // ��̨�ܵ���״̬
//  GimbalStateDebug,
//  // ��̨�Զ�����״̬
//  GimbalStateAuto,
//};

/**
 * ������̨�¼����͵�ö��
 * ��ö������������̨���ܷ����ĸ����¼���
 */
//enum GimbalEvent
//{
//  Remote_SWC_UP = 0,
//  Remote_SWC_Center,
//  Remote_SWC_Down,
//  Remote_SWA_Down,
//  Remote_SWA_Up,
//  Remote_offLine,
//};

/**
 * ����һ������ΪGimbalStateTransition�Ľṹ�壬���ڱ�ʾ��̨״̬ת����
 * �ṹ���а���������Ա��
 * nowState - ��ǰ��̨״̬������Ϊenum GimbalState��
 * event - ����״̬ת�����¼�������Ϊenum GimbalEvent��
 * nextState - ��һ����̨״̬�����ݴ������¼�ȷ��������Ϊenum GimbalState��
 */
//typedef struct
//{
//  enum GimbalState nowState;      // ��ǰ��̨״̬
//  enum GimbalEvent event;         // ������״̬ת���¼�
//  enum GimbalState nextState;    // ��һ����̨״̬
//}GimbalStateTransition;



typedef struct
{
//  enum GimbalState state;


  float Pitch_target;
  float Yaw_target;
  PID_typedef Pitch_PID_A;
  PID_typedef Pitch_PID_S;
  PID_typedef Yaw_PID_A;
  PID_typedef Yaw_PID_S;
	
  PID_typedef GyroPitch_PID_A;
  PID_typedef GyroPitch_PID_S;
  PID_typedef GyroYaw_PID_A;
  PID_typedef GyroYaw_PID_S;
	
  PID_typedef VisPitch_PID;
  PID_typedef VisYaw_PID;
	
//  struct
//  {
//    float GMtoCHError;
//    int16_t Vx;
//    int16_t Vy;
//    int16_t Vr;
//  }Chassis;
	
	uint32_t Vision_Time;
	int16_t Vision_Yanchi;
	
} Gimbal_typedef;

// ״̬���Ĵ�����ԭ�ͣ������¼�������״̬
//void processGimbalEvent(enum GimbalState *currentState, enum GimbalEvent currentEvent);
void GimbalPID_Init(void);
void Gimbal_EncoderControl(void);
void Gimbal_GyroRemote(void);
extern Gimbal_typedef Gimbal_Master;
void Gimbal_VisControl(void);
void gimbal_Remotestrafing();

#endif
