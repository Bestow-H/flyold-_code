#ifndef __MOTOR_H
#define __MOTOR_H
#include "main.h"
#include "can.h"
#include "PID.h"

#define RED   GPIO_PIN_0
#define BLUE  GPIO_PIN_9
#define GREEN GPIO_PIN_8

#define RM3508_Right_CANID 0x201
#define RM3508_Left_CANID  0x204
#define RM2006_Shoot_CANID 0x203

#define RM3510_Yaw_CANID 0x202
#define GM6020_Pitch_CANID 0x206

#define MG4005_Pitch_CANID 0x142

#define Gyro_CANID 0x110

struct Motor
{
  uint16_t rawEncode;     // ���������ص�ԭʼֵ
  uint16_t lastRawEncode; // ��һ�εı�����ԭʼֵ
  int32_t round;         // Ȧ��
  float conEncode;     // �����������ı�����ֵ
  float lastConEncode; // ��һ�εĴ���������������ֵ

  int16_t rawSpeed;     // ���ص�ת��
  int16_t lastRawSpeed; // ��һ�η��ص�ת��

  int16_t Current; // ת�ص���

  int8_t temp; // �¶�
  int ID;
  uint8_t State;
		
};


void RGB_SetColor(uint16_t color);
typedef struct
{
  struct Motor data;
  PID_typedef PID_S;
  PID_typedef PID_A;
}Motor_typedef;



extern Motor_typedef GM6020_Pitch;
extern Motor_typedef RM3508_Yaw;
extern Motor_typedef RM3508_Right;
extern Motor_typedef RM3508_Left;
extern Motor_typedef RM2006_Shoot;
extern Motor_typedef MG4005_Pitch;


void LK_MotorResolve(Motor_typedef *motor,uint8_t *RxMessage);
void MotorResolve(Motor_typedef *motor, uint8_t *RxMessage);
void MotorRoundResolve(Motor_typedef *motor);
void Motor_IDset(void);
#endif

