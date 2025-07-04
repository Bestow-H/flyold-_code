#include "_Can.h"
#include "all_line.h"


uint8_t CAN1RXmessage[8];
CAN_RxHeaderTypeDef rx1;

uint8_t CAN2RXmessage[8];
CAN_RxHeaderTypeDef rx2;

all_line status;

void CAN_Calc(CAN_HandleTypeDef* hcan, uint32_t ID);


void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef* hcan)
{
    if (hcan->Instance == CAN1) {
        HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx1, CAN1RXmessage);
        CAN_Calc(hcan, rx1.StdId);
    }

	if (hcan->Instance == CAN2) {
		HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx2, CAN2RXmessage);
        CAN_Calc(hcan, rx2.StdId);
    }
}


void CAN_Calc(CAN_HandleTypeDef* hcan, uint32_t ID)
{

    if (hcan->Instance == CAN1) {
        switch (ID) {
        case RM3508_Right_CANID: {
            MotorResolve(&RM3508_Right, CAN1RXmessage);
		      	RM3508_Right.data.State = 1;
            status.RM3508_Right_time=0;
				  	
            } break;
        case RM3508_Left_CANID: {
            MotorResolve(&RM3508_Left, CAN1RXmessage);
			      RM3508_Left.data.State = 1;
            status.RM3508_Left_time=0;
            }break;
	    	case RM2006_Shoot_CANID: {
            MotorResolve(&RM2006_Shoot, CAN1RXmessage);
		      	RM2006_Shoot.data.State = 1;
            status.RM2006_Shoot_time=0;
            }break; 
	    	case GM6020_Pitch_CANID: {
            MotorResolve(&GM6020_Pitch, CAN1RXmessage);
			      GM6020_Pitch.data.State = 1;
            } break;
		    case RM3510_Yaw_CANID: {
            MotorResolve(&RM3508_Yaw, CAN1RXmessage);
			      RM3508_Yaw.data.State = 1;
		      	status.RM3508_Yaw_time=0;
            } break;
		
		    case MG4005_Pitch_CANID: {
            LK_MotorResolve(&MG4005_Pitch, CAN1RXmessage);
		      	MG4005_Pitch.data.State = 1;
			      status.MG4005_Pitch_time=0;
            } break;
		
				case Gyro_CANID: {
				  	Gyro_Calc(&Gyro, CAN1RXmessage);
					  Gyro.State = 1;
					  status.Gyro_time=0;
								} break;
		
        default:
            break;
        }
    }
		if (hcan->Instance == CAN2) {
        switch (ID) {
		
			
			case 0x206: {
				  	MotorResolve(&RM3508_Yaw, CAN2RXmessage);
								} break;
		
        default:
            break;
			
				}
		}
}

///**
// * @brief CAN发送函数
// *
// * @param _hcan CANx
// * @param stdid 标识符
// * @param num1
// * @param num2
// * @param num3
// * @param num4
// * @return void
// */
void CAN_send(CAN_HandleTypeDef* hcan, int16_t stdid, int16_t num1, int16_t num2, int16_t num3, int16_t num4)
{
    CAN_TxHeaderTypeDef tx;
    uint8_t Data[8];
    uint32_t mailbox = 0;
    tx.DLC = 0x08;
    tx.IDE = CAN_ID_STD;
    tx.RTR = CAN_RTR_DATA;
    tx.StdId = stdid;
    tx.ExtId = 0x000;
    Data[0] = ((num1) >> 8);
    Data[1] = (num1);
    Data[2] = ((num2) >> 8);
    Data[3] = (num2);
    Data[4] = ((num3) >> 8);
    Data[5] = (num3);
    Data[6] = ((num4) >> 8);
    Data[7] = (num4);

    HAL_CAN_AddTxMessage(hcan, &tx, Data, &mailbox);
}

///**
// * @brief CAN滤波器初始化
// *
// * @param hcan CANx
// */
void CAN_Filter_Init(CAN_HandleTypeDef* hcan)
{
    CAN_FilterTypeDef sFilterConfig;
    sFilterConfig.FilterBank = 0;
    sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
    sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
    sFilterConfig.FilterIdHigh = 0x0000;
    sFilterConfig.FilterIdLow = 0x0000;
    sFilterConfig.FilterMaskIdHigh = 0x0000;
    sFilterConfig.FilterMaskIdLow = 0x0000;
    sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
    sFilterConfig.FilterActivation = ENABLE;
    sFilterConfig.SlaveStartFilterBank = 0;

    if (HAL_CAN_ConfigFilter(hcan, &sFilterConfig) != HAL_OK) {
        /* Filter configuration Error */
        Error_Handler();
        // printf("CAN configFilter Error!\r\n");
    }
    /* Start the CAN peripheral */
    if (HAL_CAN_Start(hcan) != HAL_OK) {
        /* Start Error */
        Error_Handler();
        // printf("CAN Start Error!\r\n");
    }
    /* Activate CAN RX notification */
    if (HAL_CAN_ActivateNotification(hcan, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK) {
        /* Notification Error */
        Error_Handler();
        // printf("CAN Rx Notification Error!\r\n");
    }
    /* Activate CAN TX notification */
    if (HAL_CAN_ActivateNotification(hcan, CAN_IT_TX_MAILBOX_EMPTY) != HAL_OK) {
        /* Notification Error */
        Error_Handler();
        // printf("CAN Tx Notification Error!\r\n");
    }
}

/**
************************************************************************
* @brief:      	LKMF_pos_ctrl:  单电机转矩控制函数
* @param[in]:   hcan:			指向CAN_HandleTypeDef结构的指针，用于指定CAN总线
* @param[in]:   motor_id:		电机ID，指定目标电机
* @param[in]:   vel:			位置给定值（0.01degree/LSB）
* @retval:     	void
* @details:    	通过CAN总线向电机发送位置控制命令
************************************************************************
**/
void LKMF_iq_ctrl(CAN_HandleTypeDef* hcan, uint16_t motor_id, int32_t iqControl)
{
	CAN_TxHeaderTypeDef tx;
	uint32_t mailbox = 0;
	uint8_t data[8];
		
	
	tx.StdId = 0x140 + motor_id;
	tx.IDE = CAN_ID_STD;
	tx.RTR = CAN_RTR_DATA;
	tx.DLC = 0x08;
	
	data[0] = 0xA1;
	data[1] = 0x00;
	data[2] = 0x00;
	data[3] = 0x00;
	data[4] = *(uint8_t *)(&iqControl);
	data[5] = *((uint8_t *)(&iqControl)+1);
	data[6] = 0x00;
	data[7] = 0x00;
	
	 HAL_CAN_AddTxMessage(hcan, &tx, data, &mailbox);
}

void LKMF_Data_Read(CAN_HandleTypeDef* hcan, uint16_t motor_id)
{
	CAN_TxHeaderTypeDef tx;
	uint32_t mailbox = 0;
	uint8_t data[8];	
	
	tx.StdId = 0x140 + motor_id;
	tx.IDE = CAN_ID_STD;
	tx.RTR = CAN_RTR_DATA;
	tx.DLC = 0x08;
	
	data[0] = 0x9c;
	data[1] = 0x00;
	data[2] = 0x00;
	data[3] = 0x00;
	data[4] = 0x00;
	data[5] = 0x00;
	data[6] = 0x00;
	data[7] = 0x00;
	
	 HAL_CAN_AddTxMessage(hcan, &tx, data, &mailbox);
}

