#include "_USART.h"
#include "all_line.h"
extern all_line status;
uint8_t DBUS_Data[18];
struct remoteData_typedef remote_t={0};
void DBUS_data(uint8_t *data);
uint16_t DBUS_Num;
uint8_t Vis_Data[15];

Vis_def VisMaster;

 void USER_UART_IRQHandler(UART_HandleTypeDef *huart)
{
	   if(huart->Instance == USART1)  // 判断是否是空闲中断                                 
    {	
        	 
            HAL_UART_DMAStop(&huart1);                    
			DBUS_Num = 0;
			DBUS_data(DBUS_Data);//数据解算
			status.romote_time=0;
//			printf(" ch0_int16:%d\r\n",remote_t.control.ch0_int16);
//			printf(" ch1_int16:%d\r\n",remote_t.control.ch1_int16);
//			printf(" ch2_int16:%d\r\n",remote_t.control.ch2_int16);
//			printf(" ch3_int16:%d\r\n",remote_t.control.ch3_int16);
			
			__HAL_UART_CLEAR_IDLEFLAG(&huart1);// 清除空闲中断标志（否则会一直不断进入中断）
			
			HAL_UART_Receive_DMA(&huart1, (uint8_t*)DBUS_Data, 18); // 调用中断处理函数
			
		
        
    }

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	 
	if(huart->Instance == USART2)                                 
    {	       	                    			
		HAL_UART_Receive_DMA(&huart2, (uint8_t*)Vis_Data,15); 
		Vis_Data_resolve(Vis_Data);        
    }
}

float Lasttarget,lastpre_y,lastpre_x;
uint32_t Vis_Check;
int16_t X_P=0,Y_P=70;
//http://192.168.1.1:8080/?action=stream
float GyroX,GyroY;
void Vis_Data_resolve(uint8_t * data)
{
	status.self_aiming_time=0;
	if( Vis_Data[0] == 0xcd && Vis_Data[14] == 0xdc )
	{	

		VisMaster.LastX = VisMaster.PreX;
		VisMaster.LastY = VisMaster.PreY;
		
		union visdata Visdata;
		Visdata.data[0] =  data[1];
		Visdata.data[1] =  data[2];
		Visdata.data[2] =  data[3];
		Visdata.data[3] =  data[4];
	    VisMaster.PreY  = Visdata.X_Y_data;
		
		Visdata.data[0] =  data[5];
		Visdata.data[1] =  data[6];
		Visdata.data[2] =  data[7];
		Visdata.data[3] =  data[8];
	    VisMaster.PreX  = Visdata.X_Y_data;
		
		VisMaster.States = data[9];	
		
//		if(VisMaster.PreY != VisMaster.LastY && VisMaster.PreX != VisMaster.LastX)
		if( VisMaster.States == 0x01)
		{
			Vis_Check = 0;
			
			float prey = 0.2 * VisMaster.PreY + 0.8 * lastpre_y;
			lastpre_y = prey;
			
			float prex = 0.2 * VisMaster.PreX + 0.8 * lastpre_x;
			lastpre_x = prex;
			//开启自瞄
			
			if( remote_t.control.s2_u8  == 3)
			{
				
				GyroX = (VisMaster.PreX +X_P)*14 /640;
				GyroY = (VisMaster.PreY +Y_P) *11 /512;
				
				Gimbal_Master.GyroPitch_PID_A.target  = Gyro.Pitch_angle_f  +  GyroY;
				Gimbal_Master.GyroYaw_PID_A.target    = Gyro.Yaw_angle_f    -  GyroX ;	
				
       
//				
//				Gimbal_Master.GyroPitch_PID_A.target  =  VisMaster.PreY;
//				Gimbal_Master.GyroYaw_PID_A.target    =  VisMaster.PreX ;	
			}
			VisMaster.PreY =0;
			VisMaster.PreX =0;
			
			
		}
		
//		else
//		{
//			Vis_Check++;
//			if( Vis_Check > 5)
//			{
//				Gimbal_Master.GyroPitch_PID_A.target  = Gyro.Pitch_angle_f;
//				Gimbal_Master.GyroYaw_PID_A.target = Gyro.Yaw_angle_f;
//			
//			}				
//		}
//		

 //	PID(&Gimbal_Master.VisYaw_PID, 0,  -VisMaster.PreX);
	
//	    
	
	}
	

}
uint8_t Tx[16] ;
void Vis_Tx(void)
{   
		union visdata VTdata;
		
		Tx[0] = 0xcd;Tx[15] = 0xdc;
		VTdata.X_Y_data = Gyro.Pitch_angle_f;
		Tx[1] = VTdata.data[0];
		Tx[2] = VTdata.data[1];
		Tx[3] = VTdata.data[2];
		Tx[4] = VTdata.data[3];
		
		VTdata.X_Y_data = Gyro.Yaw_angle_f;
		
		Tx[5] = VTdata.data[0];
		Tx[6] = VTdata.data[1];
		Tx[7] = VTdata.data[2];
		Tx[8] = VTdata.data[3];
//				
		HAL_UART_Transmit_DMA(&huart2,Tx ,16);

}

void DBUS_data(uint8_t *data)
{
  /*************遥控数据*************************/
	
	remote_t.control.ch0_int16	 = (data[0]    | (int16_t)data[1] <<8) & 0x07FF;														
	remote_t.control.ch1_int16	 = (data[1]>>3 | (int16_t)data[2] <<5) & 0x07FF;														
	remote_t.control.ch2_int16   = (data[2]>>6 | (int16_t)data[3] <<2| data[4]<<10) & 0x07FF;				
	remote_t.control.ch3_int16   = (data[4]>>1 | (int16_t)data[5] <<7) & 0x07FF;																									
	remote_t.control.direction	 = (data[16]   | (int16_t)data[17]<<8) & 0x07FF;														
	/* */	
	if(remote_t.control.ch0_int16&&remote_t.control.ch1_int16&&remote_t.control.ch2_int16&&remote_t.control.ch3_int16)
	{ 
	remote_t.control.ch0_int16  -= 1024;
	remote_t.control.ch1_int16  -= 1024;
	remote_t.control.ch2_int16  -= 1024;
	remote_t.control.ch3_int16  -= 1024;
	remote_t.control.direction  -= 1024;
	}
	
//	remote_t.control.direction  =0;//遥控拨盘坏了，故清零
	
	if(remote_t.control.ch0_int16 < 10 && remote_t.control.ch0_int16 > -10)
	{
		remote_t.control.ch0_int16 = 0;
	}
	if(remote_t.control.ch1_int16 < 10 && remote_t.control.ch1_int16 > -10)
	{
		remote_t.control.ch1_int16 = 0;
	}
	if(remote_t.control.ch2_int16 < 10 && remote_t.control.ch2_int16 > -10)
	{
		remote_t.control.ch2_int16 = 0;
	}
	if(remote_t.control.ch3_int16 < 10 && remote_t.control.ch3_int16 > -10)
	{
		remote_t.control.ch3_int16 = 0;
	}
	if(remote_t.control.direction < 100 && remote_t.control.direction > -100)
	{
		remote_t.control.direction = 0;
	}
	
	//
	remote_t.control.last_s1=remote_t.control.s1_u8;
	remote_t.control.last_s2=remote_t.control.s2_u8;
	remote_t.control.s1_u8 = (data[5] >> 4) & 0x03;
	remote_t.control.s2_u8 = (data[5] >> 6) & 0x03;
//	remote_t.control.direction=0;

// /*************鼠标数据**********************************************************/
//   //鼠标数据解算
 	remote_t.mouse.x=(data[6] | ( (int16_t)data[7] << 8 ));

 	remote_t.mouse.y=(data[8] | ( (int16_t)data[9] << 8 ));

 	remote_t.mouse.L=data[12];
 	remote_t.mouse.R=data[13];	
}

//void States_Resolve(void)
//{

//	
//	if(remote_t.control.s2_u8==3||remote_t.control.s2_u8==0||remote_t.mouse.L==0)
//	{
//		processShootEvent(&Shoot_Master.state, ShootEvent_SWB_UP);
//	}
//	if(remote_t.control.s2_u8==1||remote_t.mouse.L==1)
//	{
//		processShootEvent(&Shoot_Master.state, ShootEvent_SWB_Down);
//	}
//	
//}


void DBUS_offLine(void)
{
	remote_t.control.ch0_int16=0;
	remote_t.control.ch1_int16=0;
	remote_t.control.ch2_int16=0;
	remote_t.control.ch3_int16=0;
	remote_t.control.direction=0;
	remote_t.control.last_s1=0;
	remote_t.control.last_s2=0;
	remote_t.control.s1_u8=0;
	remote_t.control.s2_u8=0;
	remote_t.mouse.x=0;
	remote_t.mouse.y=0;
	remote_t.mouse.z=0;
	remote_t.mouse.L=0;
	remote_t.mouse.R=0;
}

//离线检测
void DBUS_Monitor(void)
{
	DBUS_Num++;	
	if(DBUS_Num > 50)
	{
		DBUS_offLine();
        DBUS_Num = 0;		
	}
}
