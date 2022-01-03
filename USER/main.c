#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "arm.h"
#include "led.h"
#include "usart3.h"
#include "io.h"
#include "stdlib.h"
#include "math.h"
#include "string.h"



int length,k;
double x,y,z;
int main(void)
{
    delay_init();	    	 //��ʱ������ʼ��
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
    TIM3_Int_Init(7,719);//
    TIM2_PWM_Init(999,1439);//20,60
    uart_init(9600);	 //���ڳ�ʼ��Ϊ115200
    IO_Init();
    motor[0].step=motor[1].step=motor[2].step=0;
    motor[0].stop=motor[1].stop=motor[2].stop=0;//������־��0����1����
    arm_init();
    while(1)
    {
        while(!motor[1].stop||!motor[2].stop||!motor[0].stop);
			  printf("set coordinate: x=\r\n\r\n\r\n");
        while(!(USART_RX_STA&0X8000));
			  printf("set x successfully!\r\n\r\n\r\n");			
        if(USART_RX_STA&0X8000)
        {   length=USART_RX_STA&0X7FFF;	//�õ����ݳ���
            USART_RX_BUF[length]='\0';	 	//���������
            {
                x=atof((const char*)USART_RX_BUF);
            }
            USART_RX_STA=0;
        }
        printf("x=%lf\r\n\r\n\r\n",x);
        delay_ms(50);
        printf("set coordinate: y=\r\n");
        while(!(USART_RX_STA&0X8000));
				printf("set y successfully!\r\n\r\n\r\n");
        if(USART_RX_STA&0X8000)
        {
            length=USART_RX_STA&0X7FFF;	//�õ����ݳ���
            USART_RX_BUF[length]='\0';	 	//���������
            {
                y=atof((const char*)USART_RX_BUF);
            }
            USART_RX_STA=0;
        }
        printf("y=%lf\r\n\r\n\r\n",y);
        delay_ms(50);
        printf("set coordinate: z=\r\n\r\n\r\n");
        while(!(USART_RX_STA&0X8000));
				printf("set z successfully!\r\n\r\n\r\n");
        if(USART_RX_STA&0X8000)
        {
            length=USART_RX_STA&0X7FFF;	//�õ����ݳ���
            USART_RX_BUF[length]='\0';	 	//���������
            {
                z=atof((const char*)USART_RX_BUF);
            }
            USART_RX_STA=0;
        }
        printf("z=%lf\r\n",z);
        go_coordinate(x,y,z);
        while(!motor[1].stop||!motor[2].stop||!motor[0].stop);
 
        delay_ms(500);
        printf("Reset or not?\r\n");
        while(!(USART_RX_STA&0X8000));
        if(USART_RX_STA&0X8000)
        {
            length=USART_RX_STA&0X7FFF;	//�õ����ݳ���
            USART_RX_BUF[length]='\0';	 	//���������
            if(strcmp((const char*)USART_RX_BUF,"yes")==0)
            {
							 printf("Begin to reset\r\n\r\n\r\n");
                arm_reset();
               // TIM2->CCR2=20;
            }
            USART_RX_STA=0;
        }
    }
}

