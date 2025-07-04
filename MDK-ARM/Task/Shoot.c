#include "Shoot.h"

Shoot_typedef Shoot_Master;

uint32_t time=0;

void StartShootTask(void const * argument)
{
  /* USER CODE BEGIN StartShootTask */
	
  TickType_t time = xTaskGetTickCount();

  float PID3[3] = { 6,0.1,0 };
  PID_Init(&RM3508_Right.PID_S, PID3, 1000, 4000);

  float PID4[3] = { 6,0.1,0 };
  PID_Init(&RM3508_Left.PID_S, PID4, 1000, 4000);

  float PID5[3] = { -10,0,0 };
  PID_Init(&RM2006_Shoot.PID_A, PID5, 0, 3000);
  float PID51[3] = { 10,0.00,0 };
  PID_Init(&RM2006_Shoot.PID_S, PID51, 0, 30000);

  RM2006_Shoot.PID_A.target = RM2006_Shoot.data.round * 360;

  osDelay(1000);
  /* Infinite loop */
	
		
	
  for (;;)
  {

    switch (remote_t.control.s1_u8)
    {
		case 2: {
		  Shoot_Off();
		}
		break;

		case 3: {
		  Shoot_On();
		}
		break;

		case 1: {
		  Shoot_Continue();
		}
		break;
		default:
		{
			Shoot_Off();
		
		}break;
    }

    vTaskDelayUntil(&time,4);
  }
  /* USER CODE END StartShootTask */
}


void Shoot_Off(void)
{
    RM2006_Shoot.data.round = 0;
    Shoot_Master.ShootTarget = RM2006_Shoot.data.conEncode;
	PID_clear(&RM2006_Shoot.PID_A);
	PID_clear(&RM2006_Shoot.PID_S);
	PID_clear(&RM3508_Right.PID_S);
	PID_clear(&RM3508_Left.PID_S);
	
//	PID(&RM3508_Right.PID_S, 0, RM3508_Right.data.rawSpeed);
//    PID(&RM3508_Left.PID_S,  0, RM3508_Left.data.rawSpeed);
}

void Shoot_On(void)
{
   Shoot_Wheel();
   Shoot_Master.ShootTarget = RM2006_Shoot.data.conEncode;

  PID(&RM2006_Shoot.PID_A, Shoot_Master.ShootTarget, RM2006_Shoot.data.conEncode);
  PID(&RM2006_Shoot.PID_S, RM2006_Shoot.PID_A.allOut, RM2006_Shoot.data.rawSpeed);
}

void Shoot_Continue(void)
{
   Shoot_Wheel();	
   Shoot_Shoot();
//   KaDanChack();
   PID(&RM2006_Shoot.PID_A, Shoot_Master.ShootTarget, RM2006_Shoot.data.conEncode);
   PID(&RM2006_Shoot.PID_S, RM2006_Shoot.PID_A.allOut, RM2006_Shoot.data.rawSpeed);
}


void Shoot_Wheel(void)
{
  PID(&RM3508_Right.PID_S, -6500, RM3508_Right.data.rawSpeed);
  PID(&RM3508_Left.PID_S, 6500, RM3508_Left.data.rawSpeed);
}

void Shoot_Shoot(void)
{
//	Shoot_Master.ShootCount++;

//	if(Shoot_Master.ShootCount>20)
//	{
//		Shoot_Master.ShootCount=0;
//		Shoot_Master.ShootFlag=1;		
//	}
//	
//	if (Shoot_Master.KaDan.KaDanFlag > 400)
//    {
 		Shoot_Master.ShootTarget =  0.06f * 36 * 360 + RM2006_Shoot.data.conEncode;
//    }
	
//   if (Shoot_Master.KaDan.KaDanFlag > 0)
//   {
//		Shoot_Master.KaDan.KaDanFlag--;
//   }
//   if (Shoot_Master.ShootFlag == 1 && Shoot_Master.KaDan.KaDanFlag == 0)
//   {
//		Shoot_Master.ShootFlag = 0;
//		Shoot_Master.ShootTarget -= 0.125f * 36 * 360 ;
//   }
}

void KaDanChack(void)
{
	time++;
	
  if ((time%10==0) && Shoot_Master.KaDan.KaDanFlag==0 && RM2006_Shoot.data.rawEncode ==  RM2006_Shoot.data.lastRawEncode && RM2006_Shoot.data.rawSpeed == RM2006_Shoot.data.lastRawSpeed)
  {
    Shoot_Master.KaDan.KaDanCount++;
  }
  if (Shoot_Master.KaDan.KaDanCount>=30)
  {
    Shoot_Master.KaDan.KaDanFlag=500;
    Shoot_Master.KaDan.KaDanCount=0;
  }
}