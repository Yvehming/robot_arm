#include "sys.h"
#include "arm.h"
#include "io.h"
#include "delay.h"
#include "math.h"
#include "timer.h"



#define A_max Pi/2+0.2
#define A_min -0.2
#define B_max 0.1
#define B_min -1.8              //范围限制




double angle1,angle2,angle3;//定义3个步进电机需要走的角度
extern int k;

//32个脉冲走1.8度     32*50=1600个脉冲走90度

/******* 机械臂初始化，撞到限位开关上********/

void arm_init()
{
//	    SetpMotor_SetStep(0,convert(90.0)+DELTA);
//		  SetpMotor_SetSpeed(0,2);
//      SetpMotor_SetStep(1,convert(90.0));
//		  SetpMotor_SetSpeed(1,2);

    k=1;
    while(!SWITCH_L2)
    {
        SetpMotor_SetStep(2,-1);
        SetpMotor_SetSpeed(2,2);
    }
    while(!SWITCH_L3 )
    {
        SetpMotor_SetStep(1,1);
        SetpMotor_SetSpeed(1,2);
    }
    while(!SWITCH_BASE)
    {
//        SetpMotor_SetStep(0,-1);
		SetpMotor_SetStep(0,1);
        SetpMotor_SetSpeed(0,2);
    }
    SetpMotor_SetStep(0,-(convert(110.0)));
    SetpMotor_SetSpeed(0,4);
    SetpMotor_SetStep(1,-convert(8.0));//80,32
    SetpMotor_SetSpeed(1,4);
    SetpMotor_SetStep(2,convert(6.0));
    SetpMotor_SetSpeed(2,4);
}

/******* 机械臂复位，注意顺序********/
void arm_reset()
{
     while(!SWITCH_L2)
    {
        SetpMotor_SetStep(2,-1);
        SetpMotor_SetSpeed(2,2);
    }
    while(!SWITCH_L3 )
    {
        SetpMotor_SetStep(1,1);
        SetpMotor_SetSpeed(1,2);
    }
    while(!SWITCH_BASE)
    {
//        SetpMotor_SetStep(0,-1);
		SetpMotor_SetStep(0,1);
        SetpMotor_SetSpeed(0,2);
    }
    SetpMotor_SetStep(0,-(convert(110.0)));
    SetpMotor_SetSpeed(0,4);
    SetpMotor_SetStep(1,-convert(8.0));//80,32
    SetpMotor_SetSpeed(1,4);
    SetpMotor_SetStep(2,convert(6.0));
    SetpMotor_SetSpeed(2,4);
}


/******* 坐标转角度********/
void caculate_angle(double x,double y,double z)
{
    if(y<320&&y>-320&&z>0&&z<300&&x>=0&&x<320)
    {
        double theta1,theta2,theta3,x1,y1;
        y1=z-L1;
        x1=sqrt(x*x+y*y);
        theta1=atan(y1/x1);
        theta2=acos((L2*L2+x1*x1+y1*y1-L3*L3)/(2*L2*sqrt(x1*x1+y1*y1)));
        theta3=acos((L2*L2+L3*L3-x1*x1-y1*y1)/(2*L2*L3));
        angle1=atan(y/x);
        angle2=PI/2-theta1-theta2;  //算出3个角度，弧度制
        angle3=PI-theta3+angle2-PI/2;
        //弧度转角度
        angle1*=DEGREE;
        angle2*=DEGREE;
        angle3*=DEGREE;
        if(angle1>0)
            k=1;
        if(angle1<0)
            k=-1;
        if(angle1==0)
            k=0;
    }
}

/******* 角度转步数********/
int convert(double angle)
{
    int step;
    step=(int)(angle/(1.8/SUBDIVISION)*10);//可能×10
    return step;
}

//走坐标
void go_coordinate(double x,double y,double z)
{
	int k_x,k_y,k_z;
	if(x==0)
		k_x=0;
	else
		k_x=1;
	if(y==0)
		k_y=0;
	else
		k_y=1;
	if(z==0)
		k_z=0;
	else
		k_z=1;
	
    caculate_angle(x+k_x*DELTA_X,y+k_y*DELTA_Y,z+k_z*DELTA_Z);
    SetpMotor_SetStep(1,-convert(angle2));
    SetpMotor_SetSpeed(1,2);
    SetpMotor_SetStep(2,convert(angle3));
    SetpMotor_SetSpeed(2,2);
//    SetpMotor_SetStep(0,-(convert(angle1)+k*DELTA));
	SetpMotor_SetStep(0,(convert(angle1)));
    SetpMotor_SetSpeed(0,2);
    motor[0].stop=motor[1].stop=motor[2].stop=0;
}
