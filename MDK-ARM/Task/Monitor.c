#include "Monitor.h"

//void Monitor_Init(void);
//void Monitor_offLine_Handle(void);
//void Monitor_offLine_Handle(void);

/**
 * @brief �豸����õĽṹ��
 *
 */
//struct
//{
//  uint8_t onLineChack;//chack����λ
//  uint8_t onLineStatus;//�豸״̬
//  uint8_t offLinTimeOut;//�豸��ʱʱ��
//}Monitor_root[Device_num];


/**
 * @brief ���߼��������
 *
 * @param argument
 */
//void StartMonitorTask(void const * argument)
//{
//  /* USER CODE BEGIN StartMonitorTask */
//  //��ȡʱ�����
//  TickType_t time = xTaskGetTickCount();
//  Monitor_Init();
//  /* Infinite loop */
//  /*ѭ��Ϊchack��־λ��һ*/
//  for (;;)
//  {
//    for (uint8_t i = 0; i < Device_num; i++)
//    {
//      Monitor_root[i].onLineChack++;
//      if (Monitor_root[i].onLineChack >= Monitor_root[i].offLinTimeOut)
//      {
//        Monitor_root[i].onLineStatus = offLine;
//        Monitor_offLine_Handle();
//      }
//      else
//      {
//        Monitor_root[i].onLineStatus = onLine;
//      }
//    }
//    //������ʱ10ms
//    vTaskDelayUntil(&time, 4);
//  }
//  /* USER CODE END StartMonitorTask */
//}

/**
 * @brief ���߼��ϵͳ��ʼ��
 *
 */
//void Monitor_Init(void)
//{
//  for (uint8_t i = 0; i < Device_num; i++)
//  {
//    Monitor_root[i].offLinTimeOut = 10;
//    Monitor_root[i].onLineChack = Monitor_root[i].offLinTimeOut;
//  }
//	Monitor_root[Monitor_Vision].offLinTimeOut=50;
//	Monitor_root[Monitor_SBUS].offLinTimeOut=50;
//}

/**
 * @brief ˢ�����߼�������־λ
 *
 * @param device Ҫˢ�µ��豸
 */
//void Monitor_RefreshoLineChack(uint8_t device)
//{
//  Monitor_root[device].onLineChack = 0;
//}

///**
// * @brief ϵͳ���ߴ�����
// *
// */
//void Monitor_offLine_Handle(void)
//{
//  if (Monitor_root[Monitor_Gyro].onLineStatus == offLine ||
//    Monitor_root[Monitor_SBUS].onLineStatus == offLine)
//  {
//    processGimbalEvent(&Gimbal_Master.state, Remote_offLine);
//    processShootEvent(&Shoot_Master.state, ShootEvent_OffLine);
//  }
//  else if (Monitor_root[Monitor_RM3510_Yaw].onLineStatus == offLine)
//  {
//		processGimbalEvent(&Gimbal_Master.state, Remote_offLine);
//  }
//  else if (Monitor_root[Monitor_GM6020_Pitch].onLineStatus == offLine)
//  {
//		processGimbalEvent(&Gimbal_Master.state, Remote_offLine);
//  }
//  else if (Monitor_root[Monitor_RM3508_Right].onLineStatus == offLine)
//  {
//    processShootEvent(&Shoot_Master.state, ShootEvent_OffLine);
//  }
//  else if (Monitor_root[Monitor_RM3508_Left].onLineStatus == offLine)
//  {
//    processShootEvent(&Shoot_Master.state, ShootEvent_OffLine);
//  }
//  else if (Monitor_root[Monitor_RM2006_Shoot].onLineStatus == offLine)
//  {
//    processShootEvent(&Shoot_Master.state, ShootEvent_OffLine);
//  }



//	if(Monitor_root[Monitor_SBUS].onLineStatus == offLine)
//	{
//		DBUS_offLine();
//	}
//}

//uint8_t GetShoot_Monitor_State(uint8_t Device)
//{
//	return Monitor_root[Device].onLineStatus;
//}