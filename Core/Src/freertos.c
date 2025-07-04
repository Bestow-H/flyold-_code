/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
//#include "FreeRTOSRuntimeStats.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#include "Motor.h"
#include "message_buffer.h"
#include "_Can.h"
#include "Vofa.h"
#include "all_line.h"
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for ShootTask */
osThreadId_t ShootTaskHandle;
const osThreadAttr_t ShootTask_attributes = {
  .name = "ShootTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for GimbalTask */
osThreadId_t GimbalTaskHandle;
const osThreadAttr_t GimbalTask_attributes = {
  .name = "GimbalTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for MonitorTask */
osThreadId_t MonitorTaskHandle;
const osThreadAttr_t MonitorTask_attributes = {
  .name = "MonitorTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for InitTask */
osThreadId_t InitTaskHandle;
const osThreadAttr_t InitTask_attributes = {
  .name = "InitTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityRealtime7,
};
/* Definitions for CanTask */
osThreadId_t CanTaskHandle;
const osThreadAttr_t CanTask_attributes = {
  .name = "CanTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartShootTask(void *argument);
void StartGimbalTask(void *argument);
void StartMonitorTask(void *argument);
void StartInitTask(void *argument);
void StartCanTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName);

/* USER CODE BEGIN 4 */
void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName)
{
   /* Run time stack overflow checking is performed if
   configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2. This hook function is
   called if a stack overflow is detected. */
}
/* USER CODE END 4 */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
//  UsartMessageBufferHandle = xMessageBufferCreate(256);
	
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of ShootTask */
  ShootTaskHandle = osThreadNew(StartShootTask, NULL, &ShootTask_attributes);

  /* creation of GimbalTask */
  GimbalTaskHandle = osThreadNew(StartGimbalTask, NULL, &GimbalTask_attributes);

  /* creation of MonitorTask */
  MonitorTaskHandle = osThreadNew(StartMonitorTask, NULL, &MonitorTask_attributes);

  /* creation of InitTask */
  InitTaskHandle = osThreadNew(StartInitTask, NULL, &InitTask_attributes);

  /* creation of CanTask */
  CanTaskHandle = osThreadNew(StartCanTask, NULL, &CanTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartShootTask */
/**
* @brief Function implementing the ShootTask thread.
* @param argument: Not used
* @retval None
*/
uint32_t num1,num2;
/* USER CODE END Header_StartShootTask */
__weak void StartShootTask(void *argument)
{
  /* USER CODE BEGIN StartShootTask */
  /* Infinite loop */
	
    TickType_t ShootTaskWakeTime;
   ShootTaskWakeTime = xTaskGetTickCount();
  for(;;)
  {
	  num1++;
//	  printf("num1:%d\r\n",num1);
	  RGB_SetColor(GREEN);
//	  printf("StartShootTask\r\n");
//	  printf("ShootTick:%d\r\n",xTaskGetTickCount());
//	  printf("ShootTASKByte:%d\r\n", uxTaskGetStackHighWaterMark(ShootTaskHandle));
    vTaskDelayUntil(&ShootTaskWakeTime,11);
//	  osDelay(4);
  }
  /* USER CODE END StartShootTask */
}

/* USER CODE BEGIN Header_StartGimbalTask */
/**
* @brief Function implementing the GimbalTask thread.
* @param argument: Not used
* @retval None
*/

/* USER CODE END Header_StartGimbalTask */
__weak void StartGimbalTask(void *argument)
{
  /* USER CODE BEGIN StartGimbalTask */
  /* Infinite loop */
	TickType_t GimbalTaskWakeTime;
     GimbalTaskWakeTime = xTaskGetTickCount();
  for(;;)
  {
	 

  }
  /* USER CODE END StartGimbalTask */
}

/* USER CODE BEGIN Header_StartMonitorTask */
/**
* @brief Function implementing the MonitorTask thread.
* @param argument: Not used
* @retval None
*/

/* USER CODE END Header_StartMonitorTask */
__weak void StartMonitorTask(void *argument)
{
  /* USER CODE BEGIN StartMonitorTask */
  /* Infinite loop */
	
TickType_t MonitorTaskWakeTime;
MonitorTaskWakeTime = xTaskGetTickCount();	
  for(;;)
  {
  
      
      DBUS_Monitor();
//	    all_line_check();
      vTaskDelayUntil(&MonitorTaskWakeTime,5);
  }
  /* USER CODE END StartMonitorTask */
}

/* USER CODE BEGIN Header_StartInitTask */
/**
* @brief Function implementing the InitTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartInitTask */
void StartInitTask(void *argument)
{
  /* USER CODE BEGIN StartInitTask */
  /* Infinite loop */
  for(;;)
  {
	  
	 setvbuf(stdout, NULL, _IONBF, 0);
	 __HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);
	HAL_UART_Receive_DMA(&huart1, (uint8_t*)DBUS_Data,18); 	
	HAL_UART_Receive_DMA(&huart2, (uint8_t*)Vis_Data, 15);
  	
	CAN_Filter_Init(&hcan1);
	CAN_Filter_Init(&hcan2);
	
	vTaskDelete(NULL);
	  osDelay(1); 
    
  }
  /* USER CODE END StartInitTask */
}

/* USER CODE BEGIN Header_StartCanTask */
/**
* @brief Function implementing the CanTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartCanTask */
void StartCanTask(void *argument)
{
  /* USER CODE BEGIN StartCanTask */
  /* Infinite loop */
 TickType_t CanTaskWakeTime;
 CanTaskWakeTime = xTaskGetTickCount();
 
  for(;;)
  {
	LKMF_Data_Read(&hcan1,2);
	vTaskDelayUntil(&CanTaskWakeTime,1); 
	  
	LKMF_iq_ctrl(&hcan1,2,(int16_t)Gimbal_Master.GyroPitch_PID_S.allOut); 
	vTaskDelayUntil(&CanTaskWakeTime,1); 
	  
	CAN_send(&hcan1, 0x200, (int16_t)RM3508_Right.PID_S.allOut ,(int16_t)Gimbal_Master.GyroYaw_PID_S.allOut ,(int16_t)RM2006_Shoot.PID_S.allOut ,(int16_t)RM3508_Left .PID_S.allOut);
  vTaskDelayUntil(&CanTaskWakeTime,2);
//	   CAN_send(&hcan1, 0x200, 0,00,200,000);
//  Power_on_3508check();
		
	VOFA_justfloat( Gimbal_Master.GyroPitch_PID_A.target,Gyro.Pitch_angle_f,Gimbal_Master.GyroPitch_PID_A.allOut ,Gyro.Pitch_speed,Gimbal_Master.GyroYaw_PID_A.target,Gyro.Yaw_angle_f,0,VisMaster.PreY ,VisMaster.PreX ,0);
	
//	  Vis_Tx();
	  
  }
  /* USER CODE END StartCanTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

