#include "Monitor.h"

//void Monitor_Init(void);
//void Monitor_offLine_Handle(void);
//void Monitor_offLine_Handle(void);

/**
 * @brief 设备监测用的结构体
 *
 */
//struct
//{
//  uint8_t onLineChack;//chack计数位
//  uint8_t onLineStatus;//设备状态
//  uint8_t offLinTimeOut;//设备超时时间
//}Monitor_root[Device_num];


/**
 * @brief 离线监测任务函数
 *
 * @param argument
 */
//void StartMonitorTask(void const * argument)
//{
//  /* USER CODE BEGIN StartMonitorTask */
//  //获取时间节拍
//  TickType_t time = xTaskGetTickCount();
//  Monitor_Init();
//  /* Infinite loop */
//  /*循环为chack标志位加一*/
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
//    //绝对延时10ms
//    vTaskDelayUntil(&time, 4);
//  }
//  /* USER CODE END StartMonitorTask */
//}

/**
 * @brief 离线监测系统初始化
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
 * @brief 刷新离线监测计数标志位
 *
 * @param device 要刷新的设备
 */
//void Monitor_RefreshoLineChack(uint8_t device)
//{
//  Monitor_root[device].onLineChack = 0;
//}

///**
// * @brief 系统离线处理函数
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