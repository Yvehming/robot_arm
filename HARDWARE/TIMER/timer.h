#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////
//¶¨Ê±Æ÷£¬PWM
//********************************************************************************

void TIM3_Int_Init(u16 arr,u16 psc);
void TIM2_PWM_Init(u16 arr,u16 psc);
void SetpMotor_SetStep(int id, int steps);
void SetpMotor_SetSpeed(int id, int speed);
void TIM7_Int_Init(u16 arr,u16 psc);

typedef struct {
    int step;
    int target;
    int div;
	int stop;
} StepMotor;
extern StepMotor motor[3];



#endif
