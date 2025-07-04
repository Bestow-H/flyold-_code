#include "Motor.h"

Motor_typedef GM6020_Pitch;
Motor_typedef RM3508_Yaw;
Motor_typedef RM3508_Right;
Motor_typedef RM3508_Left;
Motor_typedef RM2006_Shoot;
Motor_typedef MG4005_Pitch;

void Motor_IDset(void)
{
	GM6020_Pitch.data.ID  = GM6020_Pitch_CANID;
	RM3508_Yaw.data.ID    = RM3510_Yaw_CANID;
	RM3508_Right.data.ID  = RM3508_Right_CANID;
	RM3508_Left.data.ID   = RM3508_Left_CANID;
	RM2006_Shoot.data.ID  = RM2006_Shoot_CANID;
}

void LK_MotorResolve(Motor_typedef *motor,uint8_t *RxMessage)
{
	if(RxMessage[0]==0x9c)
	{
		motor->data.temp = RxMessage[1];
	
		motor->data.Current = ((uint16_t)RxMessage[3] << 8 | (uint16_t)RxMessage[2]);
	
		motor->data.lastRawSpeed = motor->data.rawSpeed;
		motor->data.rawSpeed     = ((uint16_t)RxMessage[5] << 8 | (uint16_t)RxMessage[4]);
		
		motor->data.lastRawEncode = motor->data.rawEncode;
		motor->data.rawEncode     = ((uint16_t)RxMessage[7] << 8 | (uint16_t)RxMessage[6]);
		
		if(motor->data.State)
		{
			if (motor->data.rawEncode - motor->data.lastRawEncode < -40000) 
			{
				motor->data.round++;
			}
			else if (motor->data.rawEncode - motor->data.lastRawEncode > 40000) 
			{
				motor->data.round--;
			}
			motor->data.lastConEncode = motor->data.conEncode;
			motor->data.conEncode     = (float) motor->data.round* 360 + (float) motor->data.rawEncode * 360 / 65536;	
		}
		else
		{
			motor->data.conEncode=(float)motor->data.rawEncode * 360 / 65536;	
		} 
	}
	

}
void MotorResolve(Motor_typedef *motor, uint8_t *RxMessage)
{
    /*编码器值解算*/
    motor->data.lastRawEncode = motor->data.rawEncode;
    motor->data.rawEncode     = ((uint16_t)RxMessage[0] << 8 | (uint16_t)RxMessage[1]);
    /*速度解算*/
    motor->data.lastRawSpeed = motor->data.rawSpeed;
    motor->data.rawSpeed     = ((uint16_t)RxMessage[2] << 8 | (uint16_t)RxMessage[3]);
    /*转矩电流*/
    motor->data.Current = ((uint16_t)RxMessage[4] << 8 | (uint16_t)RxMessage[5]);
    /*电机温度*/
    motor->data.temp = RxMessage[6];
	
	MotorRoundResolve(motor);
}



void MotorRoundResolve(Motor_typedef *motor)
{    
	if(motor->data.State)
	{
		if (motor->data.rawEncode - motor->data.lastRawEncode < -4096) 
		{
			motor->data.round++;
		}
		else if (motor->data.rawEncode - motor->data.lastRawEncode > 4096) 
		{
			motor->data.round--;
		}
		motor->data.lastConEncode = motor->data.conEncode;
		motor->data.conEncode     = (float)motor->data.round * 360 + (float)motor->data.rawEncode * 360 / 8192;	
	}
	else
	{
		motor->data.conEncode=motor->data.rawEncode * 360 / 65536;	
	}   
}

void RGB_SetColor(uint16_t color)
{
	
	switch(color)
	{
		case RED :
		{
		    HAL_GPIO_WritePin(GPIOE,RED,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB,GREEN,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,BLUE,GPIO_PIN_SET);
		};break;
		case GREEN :
		{
		    HAL_GPIO_WritePin(GPIOB,GREEN,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOE,RED,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,BLUE,GPIO_PIN_SET);
		};break;
		case BLUE :
		{
		    HAL_GPIO_WritePin(GPIOB,BLUE,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOE,RED,GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB,GREEN,GPIO_PIN_SET);
		};break;
		
	}
}