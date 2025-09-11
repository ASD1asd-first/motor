#include <REGX52.H>
#include "motor.h"

unsigned int delay_count = 0;
unsigned int delay = 10;
unsigned char delay_on = 0;

void Timer0_Init(void)		//1����@11.0592MHz
{
	TMOD &= 0xF0;			//���ö�ʱ��ģʽ
	TMOD |= 0x01;			//��ʱ��ģʽ
	TL0 = 0x66;				//���ö�ʱ��ʼֵ
	TH0 = 0xFC;				//���ö�ʱ��ʼֵ
	TF0 = 0;				//���TF0��־
	TR0 = 1;				//��ʱ��0��ʼ��ʱ
	EA = 1;					//ʹ�������ж�
	ET0 = 1;				//ʹ�ܶ�ʱ��0�ж�
	PT0 = 0;				//���ȼ���
}


void main(void){
	unsigned char choose = 0;
	unsigned char choose_on = 0;
	Timer0_Init();
	Motor_Init();
	while(1){
		if(P3_1==0){
			while(P3_1==0);
			choose_on = 0;
		}else if(P3_0==0){
			while(P3_0==0);
			choose_on = 1;
		}else if(P3_2==0){
			while(P3_2==0);
			choose_on = 2;
		}
		if(delay_on){
			delay_on = 0;
			if(choose_on == 1){
				Motor_Init();
				Motor_Forwarding(choose);
			}else if(choose_on == 2){
				Motor_Init();
				Motor_Backing(choose);
			}
			choose ++;
			choose = choose % 8;
		}
	}
}

void setting(void) interrupt 1 using 1{
	TL0 = 0x66;				//���ö�ʱ��ʼֵ
	TH0 = 0xFC;				//���ö�ʱ��ʼֵ
	delay_count++;
	if(delay_count >= delay){
		delay_count = 0;
		delay_on = 1;
	}
}
