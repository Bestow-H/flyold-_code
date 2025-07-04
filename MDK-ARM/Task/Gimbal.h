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
//  // 云台停止状态
//  GimbalStateStop = 0,
//  // 云台受遥控状态
//  GimbalStateRemote,
//  // 云台受调试状态
//  GimbalStateDebug,
//  // 云台自动控制状态
//  GimbalStateAuto,
//};

/**
 * 定义云台事件类型的枚举
 * 该枚举用于描述云台可能发生的各种事件。
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
 * 定义一个名称为GimbalStateTransition的结构体，用于表示云台状态转换。
 * 结构体中包含三个成员：
 * nowState - 当前云台状态，类型为enum GimbalState；
 * event - 触发状态转换的事件，类型为enum GimbalEvent；
 * nextState - 下一个云台状态，根据触发的事件确定，类型为enum GimbalState。
 */
//typedef struct
//{
//  enum GimbalState nowState;      // 当前云台状态
//  enum GimbalEvent event;         // 触发的状态转换事件
//  enum GimbalState nextState;    // 下一个云台状态
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

// 状态机的处理函数原型，接收事件并更新状态
//void processGimbalEvent(enum GimbalState *currentState, enum GimbalEvent currentEvent);
void GimbalPID_Init(void);
void Gimbal_EncoderControl(void);
void Gimbal_GyroRemote(void);
extern Gimbal_typedef Gimbal_Master;
void Gimbal_VisControl(void);
void gimbal_Remotestrafing();

#endif
