#ifndef __SHOOT_H
#define __SHOOT_H
#include "main.h"
#include "Motor.h"
#include "PID.h"
#include "_Can.h"
#include "freertos.h"
#include "cmsis_os.h"
#include "Monitor.h"

enum ShootState
{
	ShootStateOff=0,
	ShootStateOn,
	ShootStateContinue,
	ShootStateAuto,
};

typedef struct
{
	enum ShootState state;
	float ShootTarget;
	uint8_t ShootFlag;
	uint16_t ShootCount;
	
	uint8_t OffLine_Flag;

	struct
	{
		uint16_t KaDanFlag;
		uint16_t KaDanCount;
		uint16_t KaDanThreshold;
	}KaDan;

}Shoot_typedef;

extern Shoot_typedef Shoot_Master;
void Shoot_Off(void);
void Shoot_On(void);
void Shoot_Continue(void);


void Shoot_Wheel(void);
void Shoot_Shoot(void);
void KaDanChack(void );

#endif

