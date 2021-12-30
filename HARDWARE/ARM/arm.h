#ifndef __ARM_H
#define __ARM_H

#include "sys.h"

#define SWITCH_BASE    PCin(11)
#define SWITCH_L2      PAin(4)
#define SWITCH_L3      PCin(10)

#define DELTA_X 20
#define DELTA_Y 20
#define DELTA_Z 15

#define L1 110       //机械臂臂长
#define L2 135
#define L3 160

#define PI 3.141592654
#define DEGREE  180/PI
#define SUBDIVISION  8
#define DELTA        convert(25.0)
#define COEFFICIENT   125/90

extern double angle1,angle2,angle3;//定义3个步进电机需要走的角度
void arm_init(void);
void arm_reset(void);
void caculate_angle(double x,double y,double z);
int convert(double angle);
void go_coordinate(double x,double y,double z);

#endif

