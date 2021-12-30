#ifndef __IO_H
#define __IO_H
#include "sys.h"

#define PA_out GPIOA_ODR_Addr 
#define PB_out GPIOB_ODR_Addr
#define PC_out GPIOC_ODR_Addr
#define PD_out GPIOD_ODR_Addr
#define PE_out GPIOE_ODR_Addr
#define PF_out GPIOF_ODR_Addr
#define PG_out GPIOG_ODR_Addr



typedef struct
{
	u32 GPIO;
	int n;
}
IO;

//extern IO B_out[16];



void IO_Init(void);

#endif
