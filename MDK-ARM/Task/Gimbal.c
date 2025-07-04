#include "Gimbal.h"

Gimbal_typedef Gimbal_Master;
void Gimbal_Stop(void);
void Gimbal_Remote(void);
void Gimbal_GyroControl(void);
float correct=0;
float Gyrotemp=0;
float a=0;
float b=0;

int32_t GimbalTaskState ; 
void StartGimbalTask(void const * argument)
{
  /* USER CODE BEGIN StarChassisTask */
  TickType_t time = xTaskGetTickCount();
  	
  Motor_IDset();
  GimbalPID_Init();	
   osDelay(1000);
  /* Infinite loop */
  for (;;)
  {

    switch(remote_t.control.s2_u8)
		{
			case 0 :
			{
				Gimbal_Stop();
				GimbalTaskState = 0;
				a=0;
				b=0;
			}break;
			case 1 :
			{
				Gimbal_Stop();
				GimbalTaskState = 1;
				
			}break;
			
			case 3 :
			{
				Gimbal_GyroRemote(); 
   			Gimbal_VisControl();
//				Gimbal_EncoderControl();
				GimbalTaskState = 3;
				a=Gimbal_Master.GyroPitch_PID_A.target;
				b=Gimbal_Master.GyroYaw_PID_A.target;
			}break;
			case 2 :
			{
//				Gimbal_GyroRemote();
				gimbal_Remotestrafing();
				Gimbal_GyroControl();
				GimbalTaskState = 2;
				
			}break;
			default:
			{
				Gimbal_Stop();
		
			}break;
		} 

    vTaskDelayUntil(&time, 3);
  }
  /* USER CODE END StarChassisTask */
}
void GimbalPID_Init(void)
{
  //编码器部分
	
//  float PID1[3] = { 0,0,0 };
//  PID_Init(&Gimbal_Master.Pitch_PID_A, PID1, 0, 100);
//  float PID11[3] = { 0,0,0 };
//  PID_Init(&Gimbal_Master.Pitch_PID_S, PID11, 0, 200);

//  float PID2[3] = { 1.2,0,0.5};
//  PID_Init(&Gimbal_Master.Yaw_PID_A, PID2, 50, 300);
//  float PID21[3] = { 65,0,3};
//  PID_Init(&Gimbal_Master.Yaw_PID_S, PID21, 0, 15000);
  //陀螺仪部分
//  float PID_G_P_A[3] = {0.026f,0.00003,0};
	float PID_G_P_A[3] = {0.02,0.00000,0};
  PID_Init( & Gimbal_Master.GyroPitch_PID_A , PID_G_P_A ,0.02  , 100);
//  float PID_G_P_S[3] = {550,0,0};
	float PID_G_P_S[3] = {1200 ,0,0};
  PID_Init( & Gimbal_Master.GyroPitch_PID_S , PID_G_P_S ,0 , 400);
  
//  float PID_G_Y_A[3] = {0.05,0,0};
  float PID_G_Y_A[3] = {0.013,0,0};
  PID_Init( & Gimbal_Master.GyroYaw_PID_A , PID_G_Y_A ,0 , 10);
//  float PID_G_Y_S[3] = {-80000,0,0};
  float PID_G_Y_S[3] = {-85000,0,0};
  PID_Init( & Gimbal_Master.GyroYaw_PID_S , PID_G_Y_S ,0 , 15000);
  
  //视觉部分
  
  float PID_V_P[3] = {0.015,0,0};
  PID_Init( & Gimbal_Master.VisPitch_PID , PID_V_P ,0 , 10);
  float PID_V_Y[3] = {0,0,0};
  PID_Init( & Gimbal_Master.VisYaw_PID , PID_V_Y ,0 , 0);
}


void Gimbal_Stop(void)
{
  Gimbal_Master.GyroPitch_PID_A.target =   Gyro.Pitch_angle_f;
  Gimbal_Master.GyroYaw_PID_A.target =  Gyro.Yaw_angle_f;
	
  Gimbal_Master.Pitch_target = MG4005_Pitch.data.conEncode;
  Gimbal_Master.Yaw_target =RM3508_Yaw.data.conEncode;
  PID_clear(&Gimbal_Master.Pitch_PID_A);
  PID_clear(&Gimbal_Master.Pitch_PID_S);
  PID_clear(&Gimbal_Master.Yaw_PID_A);
  PID_clear(&Gimbal_Master.Yaw_PID_S);
	
  PID_clear(&Gimbal_Master.GyroPitch_PID_A);
  PID_clear(&Gimbal_Master.GyroPitch_PID_S);	
  PID_clear(&Gimbal_Master.GyroYaw_PID_A);
  PID_clear(&Gimbal_Master.GyroYaw_PID_S);
	
  PID_clear(&Gimbal_Master.VisPitch_PID);
  PID_clear(&Gimbal_Master.VisYaw_PID);
	
}

uint16_t Yaw_Count=0;
//void Gimbal_Remote(void)
//{
//  Gimbal_Master.Pitch_PID_A.target += ((float)remote_t.control.ch3_int16)*0.001f;
//  Gimbal_Master.Yaw_PID_A.target += ((float)remote_t.control.ch2_int16)*0.001f;
	
//	Gimbal_Master.Pitch_target -= MouseY_averageFilter((float)remote_t.mouse.y)*0.1f;
//  Gimbal_Master.Yaw_target += MouseX_averageFilter((float)remote_t.mouse.x)*0.1f;
//}

void Gimbal_GyroRemote(void)
{
  Gimbal_Master.GyroPitch_PID_A.target += ((float)remote_t.control.ch3_int16)*0.001f;
  Gimbal_Master.GyroYaw_PID_A.target -= ((float)remote_t.control.ch2_int16)*0.001f;
	
//	Gimbal_Master.Pitch_target -= MouseY_averageFilter((float)remote_t.mouse.y)*0.1f;
//  Gimbal_Master.Yaw_target += MouseX_averageFilter((float)remote_t.mouse.x)*0.1f;
}

float IntervalLimit(float max, float min, float data)
{
  if (max >= min)
  {
    if (data >= max)return max;
    else if (data <= min)return min;
    else return data;
  }
  else
  {
    float temp;
    temp = min;
    min = max;
    max = temp;

    if (data >= max)return max;
    else if (data <= min)return min;
    else return data;
  }
}

void Gimbal_EncoderControl(void)
{
	if(GimbalTaskState != 3)
	{
		Gimbal_Master.Pitch_PID_A.target =   MG4005_Pitch.data.conEncode;
		Gimbal_Master.Yaw_PID_A.target   =  RM3508_Yaw.data.conEncode;
    }
  /*Pitch轴限幅*/
  Gimbal_Master.Pitch_PID_A.target = IntervalLimit(Pitch_Upper_Limit, Pitch_Lower_Limit, Gimbal_Master.Pitch_PID_A.target );
  Gimbal_Master.Yaw_PID_A.target = IntervalLimit(Yaw_Upper_Limit, Yaw_Lower_Limit,  Gimbal_Master.Yaw_PID_A.target);

  PID(&Gimbal_Master.Pitch_PID_A, Gimbal_Master.Pitch_PID_A.target, MG4005_Pitch.data.conEncode);
  PID(&Gimbal_Master.Pitch_PID_S, Gimbal_Master.Pitch_PID_A.allOut,MG4005_Pitch.data.rawSpeed);
	
  PID(&Gimbal_Master.Yaw_PID_A, Gimbal_Master.Yaw_PID_A.target, RM3508_Yaw.data.conEncode);
  PID(&Gimbal_Master.Yaw_PID_S, Gimbal_Master.Yaw_PID_A.allOut,RM3508_Yaw.data.rawSpeed);  
}

void Gimbal_GyroControl(void)
{
	if(GimbalTaskState != 2)
	{
		Gimbal_Master.GyroPitch_PID_A.target =   Gyro.Pitch_angle_f;
		Gimbal_Master.GyroYaw_PID_A.target =  Gyro.Yaw_angle_f;
	}

/*让目标值始终保持在数据范围内*/	
  Gimbal_Master.GyroPitch_PID_A.target = IntervalLimit(Gyro_Pitch_Upper_Limit, Gyro_Pitch_Lower_Limit, Gimbal_Master.GyroPitch_PID_A.target );  
  Gimbal_Master.GyroYaw_PID_A.target =   IntervalLimit(Gyro_Yaw_Upper_Limit, Gyro_Yaw_Lower_Limit,  Gimbal_Master.GyroYaw_PID_A.target);
	
  PID(&Gimbal_Master.GyroPitch_PID_A, Gimbal_Master.GyroPitch_PID_A.target,  Gyro.Pitch_angle_f);
  PID(&Gimbal_Master.GyroPitch_PID_S, Gimbal_Master.GyroPitch_PID_A.allOut, Gyro.Pitch_speed);
	
  PID(&Gimbal_Master.GyroYaw_PID_A, Gimbal_Master.GyroYaw_PID_A.target, Gyro.Yaw_angle_f);
  PID(&Gimbal_Master.GyroYaw_PID_S, Gimbal_Master.GyroYaw_PID_A.allOut,Gyro.Yaw_speed);
  /*CAN发送云台控制数据*/
	
  Gimbal_Master.Yaw_PID_S.allOut = Gimbal_Master.GyroYaw_PID_S.allOut;
}

void Gimbal_VisControl(void)
{
	if(GimbalTaskState != 3)
	{
		Gimbal_Master.GyroPitch_PID_A.target =   Gyro.Pitch_angle_f;
		Gimbal_Master.GyroYaw_PID_A.target =  Gyro.Yaw_angle_f;
	}

//	PID(&Gimbal_Master.VisPitch_PID, 0,  -VisMaster.PreY);
	
/*让目标值始终保持在数据范围内*/	
  Gimbal_Master.GyroPitch_PID_A.target = IntervalLimit(Gyro_Pitch_Upper_Limit, Gyro_Pitch_Lower_Limit, Gimbal_Master.GyroPitch_PID_A.target );  
  Gimbal_Master.GyroYaw_PID_A.target =   IntervalLimit(Gyro_Yaw_Upper_Limit, Gyro_Yaw_Lower_Limit,  Gimbal_Master.GyroYaw_PID_A.target);
	
  PID(&Gimbal_Master.GyroPitch_PID_A, Gimbal_Master.GyroPitch_PID_A.target ,  Gyro.Pitch_angle_f);	
  PID(&Gimbal_Master.GyroPitch_PID_S, Gimbal_Master.GyroPitch_PID_A.allOut  , Gyro.Pitch_speed);
	
  PID(&Gimbal_Master.GyroYaw_PID_A, Gimbal_Master.GyroYaw_PID_A.target, Gyro.Yaw_angle_f);	
  PID(&Gimbal_Master.GyroYaw_PID_S, Gimbal_Master.GyroYaw_PID_A.allOut , Gyro.Yaw_speed);
  /*CAN发送云台控制数据*/
	
//  Gimbal_Master.Yaw_PID_S.allOut = Gimbal_Master.GyroYaw_PID_S.allOut;
}
//状态转移表
//static GimbalStateTransition StateTransition[16] =
//{
//  {GimbalStateStop, Remote_offLine, GimbalStateStop},
//  {GimbalStateStop, Remote_SWC_UP, GimbalStateStop},
//  {GimbalStateStop, Remote_SWC_Center, GimbalStateRemote},
//  {GimbalStateStop, Remote_SWC_Down, GimbalStateAuto},

//  {GimbalStateRemote, Remote_offLine, GimbalStateStop},
//  {GimbalStateRemote, Remote_SWC_UP, GimbalStateStop},
//  {GimbalStateRemote, Remote_SWC_Center, GimbalStateRemote},
//  {GimbalStateRemote, Remote_SWC_Down, GimbalStateAuto},
//  {GimbalStateRemote, Remote_SWA_Down, GimbalStateDebug},

//  {GimbalStateAuto, Remote_offLine, GimbalStateStop},
//  {GimbalStateAuto, Remote_SWC_UP, GimbalStateStop},
//  {GimbalStateAuto, Remote_SWC_Center, GimbalStateRemote},
//  {GimbalStateAuto, Remote_SWC_Down, GimbalStateAuto},
//  {GimbalStateAuto, Remote_SWA_Down, GimbalStateDebug},

//  {GimbalStateDebug,Remote_SWA_Up,GimbalStateRemote},
//  {GimbalStateDebug,Remote_offLine,GimbalStateStop},
//};

/**
 * 处理云台事件的函数
 *
 * 根据当前的云台状态和发生的事件，更新云台的状态。
 *
 * @param currentState 指向当前云台状态的指针，函数会根据事件更新此状态。
 * @param currentEvent 当前发生的云台事件。
 */
//void processGimbalEvent(enum GimbalState *currentState, enum GimbalEvent currentEvent)
//{
//  // 遍历状态转换表，查找与当前状态和事件匹配的转换
//  for (uint8_t i = 0; i < 16; i++)
//  {
//    if (StateTransition[i].nowState == *currentState &&
//        StateTransition[i].event == currentEvent)
//    {
//      // 找到匹配项，更新云台状态到下一个状态
//      *currentState = StateTransition[i].nextState;

//			if(*currentState >=4)
//				{
//					while(1);
//					}
//      break;
//    }
//  }
//  return ;
//}
void gimbal_Remotestrafing()
{
  Gimbal_Master.GyroPitch_PID_A.target=a+((float)remote_t.control.ch3_int16)*0.034;
	Gimbal_Master.GyroYaw_PID_A.target =b-((float)remote_t.control.ch2_int16)*0.0454;
}


