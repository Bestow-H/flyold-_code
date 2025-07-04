#ifndef __GYROSCOPE_H
#define __GYROSCOPE_H
#include "main.h"

#define now  1
#define last 0


typedef struct
{
	
	float   Yaw_angle_f;
	
	float   Pitch_angle_f;
	
	float Yaw_speed;
	float Pitch_speed;
	
	
	float   LastPitch_angle_f;
	float   LastYaw_angle_f;
	
	float   LastPitch_speed;
	float   LastYaw_speed;
	
	uint8_t State;
	
//	float Q0;
//	float Q1;
//	float Q2;
//	float Q3;
}Gyroscope_typedef;
extern Gyroscope_typedef Gyro;
void Gyro_Calc(Gyroscope_typedef *gyro ,uint8_t data[8]);
uint8_t GyroToEncoder(float* gyro, uint16_t Encoder, float* data);

#endif
