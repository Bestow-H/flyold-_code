#ifndef ___CAN_H
#define ___CAN_H
#include "main.h"
#include "can.h"
#include "Motor.h"
#include "Gimbal.h"
void CAN_Filter_Init(CAN_HandleTypeDef* hcan);
void CAN_send(CAN_HandleTypeDef* hcan, int16_t stdid, int16_t num1, int16_t num2, int16_t num3, int16_t num4);
void LKMF_Data_Read(CAN_HandleTypeDef* hcan, uint16_t motor_id);
void LKMF_iq_ctrl(CAN_HandleTypeDef* hcan, uint16_t motor_id, int32_t iqControl);
#endif

