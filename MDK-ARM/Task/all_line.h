#ifndef __ALL_LINE_H
#define __ALL_LINE_H
#include "main.h"
#define off_line 0
#define on_Line  1
typedef struct {
  uint8_t RM3508_Yaw_status;
	uint8_t RM3508_Yaw_time;
	uint8_t RM3508_Right_status;
	uint8_t RM3508_Right_time;
	uint8_t RM3508_Left_status;
	uint8_t RM3508_Left_time;
	uint8_t RM2006_Shoot_status;
	uint8_t RM2006_Shoot_time;
	uint8_t MG4005_Pitch_status;
	uint8_t MG4005_Pitch_time;
	uint8_t romote_status;
	uint8_t romote_time;  
	uint8_t Gyro_status;
	uint8_t Gyro_time;
	uint8_t power_on_3508stutas;
	uint8_t self_aiming_status;
	uint8_t self_aiming_time;
	
} all_line;
extern all_line status;
void all_line_check();
void Power_on_3508check();
#endif