#include "Gyroscope.h"
#include "math.h"
Gyroscope_typedef Gyro;
void Gyro_Calc(Gyroscope_typedef* gyro, uint8_t data[8])
{
	//Yaw�Ƕ�
	gyro-> LastYaw_angle_f = gyro->Yaw_angle_f;
	int16_t angle= (int16_t)data[1] << 8 | data[0];
	gyro->Yaw_angle_f = angle * -0.0125f;

	//Pitch�Ƕ�
	gyro->LastPitch_angle_f = gyro->Pitch_angle_f;
	angle = (int16_t)data[3] << 8 | data[2];
	gyro->Pitch_angle_f = angle * 0.0125f;

//	//Yaw�ٶ� 
//	gyro->Yaw_speed = gyro->Yaw_speed;
	gyro->Yaw_speed = gyro->Yaw_angle_f - gyro-> LastYaw_angle_f;
//	gyro->Yaw_speed_f = gyro->Yaw_speed * 0.01f;

//	//Pitch�ٶ�
//	gyro->Pitch_speed = gyro->Pitch_speed;
	gyro->Pitch_speed = gyro->Pitch_angle_f - gyro->LastPitch_angle_f;
//	gyro->Pitch_speed_f = gyro->Pitch_speed * 0.01f;
	
//	gyro->Q0 = ((float)( ( int16_t ) data[1] << 8 | data[0] )) * 0.0001f;
//	gyro->Q1 = ((float)( ( int16_t ) data[3] << 8 | data[2] )) * 0.0001f;
//	gyro->Q2 = ((float)( ( int16_t ) data[5] << 8 | data[4] )) * 0.0001f;
//	gyro->Q3 = ((float)( ( int16_t ) data[7] << 8 | data[6] )) * 0.0001f;
//	
//	gyro->Yaw_angle = atan2(2.0 * (gyro->Q0 * gyro->Q3 + gyro->Q1 * gyro->Q2), 1.0 - 2.0 * (gyro->Q2 * gyro->Q2 + gyro->Q3 * gyro->Q3)) * 180.00f / 3.14159;
//	gyro->Pitch_angle = asin(2.0 * (gyro->Q0 * gyro->Q2 - gyro->Q3 * gyro->Q1))* 180.00f / 3.14159;
}

/**
 * ������������ת��Ϊ����������
 *
 * @param gyro ָ�����������ݵĸ���ָ�룬��λΪ��
 * @param Encoder ����������Ȧ����ֵ
 * @param data ָ��洢ת�������ݵĸ���ָ��
 *
 * @note ���gyro��dataΪNULL�������������أ���ִ��ת����
 */
uint8_t GyroToEncoder(float* gyro, uint16_t Encoder, float* data)
{
    // �������ָ���Ƿ�ΪNULL������ǣ���ִ���κβ���
	if (gyro == NULL || data == NULL)return 0;

    // �����������ݳ��Ա�����������360�ȵı�ֵ�����ת��
	*data = *gyro * ((float)Encoder / 360.0f);
	return 1;
}