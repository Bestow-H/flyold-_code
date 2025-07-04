#ifndef ___USART_H
#define ___USART_H
#include "main.h"
#include "usart.h"
#include <stdio.h>
#include "freertos.h"
#include "task.h"          // 引入头文件
#include "message_buffer.h"
#include "stdint.h"
#include "Shoot.h"
#include "Gimbal.h"


#define dbus_Length 18

struct remoteData_typedef
{
	struct
	{
		int16_t ch0_int16;
		int16_t ch1_int16;
		int16_t ch2_int16;
		int16_t ch3_int16;
		uint8_t s1_u8;
		uint8_t s2_u8;
		uint8_t last_s1;
		uint8_t last_s2;
		int16_t direction;
	}control;
	struct
	{
		int16_t x;
		int16_t y;
		int16_t z;
		uint8_t L:1;
		uint8_t R:1;
	}mouse;
//	struct
//	{
//		
//	}keyboard;
};
union visdata
{
		float X_Y_data;
		uint8_t data[4];		
};

typedef struct
{
	float X;//x坐标
	float Y;//y坐标

	float LastX;//上一次x坐标
	float LastY;//上一次y坐标

	float PreX;//预测x坐标
	float PreY;//预测y坐标
		
	uint8_t States;//状态
	
	
	
}Vis_def;


void DBUS_data(uint8_t *data);
void DBUS_offLine(void);

extern uint8_t DBUS_Data[dbus_Length];
extern uint8_t Vis_Data[15];
extern Vis_def VisMaster;
extern struct remoteData_typedef remote_t;

void Vis_Data_resolve(uint8_t * data);
void USER_UART_IRQHandler(UART_HandleTypeDef *huart);

void DBUS_Monitor(void);


void Vis_Tx(void);


#endif
