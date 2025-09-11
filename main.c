#include <REGX52.H>
#include "motor.h"

unsigned int delay_count = 0;
unsigned int delay = 10;
unsigned char delay_on = 0;

void Timer0_Init(void)		//1毫秒@11.0592MHz
{
	TMOD &= 0xF0;			//设置定时器模式
	TMOD |= 0x01;			//定时器模式
	TL0 = 0x66;				//设置定时初始值
	TH0 = 0xFC;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
	EA = 1;					//使能所有中断
	ET0 = 1;				//使能定时器0中断
	PT0 = 0;				//优先级低
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
	TL0 = 0x66;				//设置定时初始值
	TH0 = 0xFC;				//设置定时初始值
	delay_count++;
	if(delay_count >= delay){
		delay_count = 0;
		delay_on = 1;
	}
}
