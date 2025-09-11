#include <REGX52.H>

sbit a_for = P2^0;
sbit a_bak = P2^1;
sbit b_for = P2^2;
sbit b_bak = P2^3;

static void a_forward(void){//A+
	a_for = 1;
	a_bak = 0;
}

static void a_back(void){//A-
	a_for = 0;
	a_bak = 1;
}

static void b_forward(void){//B+
	b_for = 1;
	b_bak = 0;
}

static void b_back(void){//B-
	b_for = 0;
	b_bak = 1;
}

static void stop(void){
	a_for = 0;
	a_bak = 0;
	b_for = 0;
	b_bak = 0;
}
/**
 *	@function:步进电机正转,
 *	@param choose: 表示步进电机正转节拍数
 *	本步进电机采用八拍控制方式,从零开始计次
 */
void Motor_Forwarding(unsigned char choose){
	switch(choose){
		case 0: stop(); b_back(); a_forward(); break;      
		case 1: stop(); a_forward(); break;     
		case 2: stop(); a_forward(); b_forward(); break;    
		case 3: stop(); b_forward(); break;       
		case 4: stop(); b_forward(); a_back(); break;       
		case 5: stop(); a_back(); break;    
		case 6: stop(); a_back(); b_back(); break;    
		case 7: stop(); b_back(); break;       
	}
}

/**
 *	@function:步进电机反转,
 *	@param choose: 表示步进电机反转节拍数
 *	本步进电机采用八拍控制方式,从零开始计次
*/
void Motor_Backing(unsigned char choose){
	switch(choose){
		case 7: stop(); b_back(); a_forward(); break;      
		case 6: stop(); a_forward(); break;     
		case 5: stop(); a_forward(); b_forward(); break;    
		case 4: stop(); b_forward(); break;       
		case 3: stop(); b_forward(); a_back(); break;       
		case 2: stop(); a_back(); break;    
		case 1: stop(); a_back(); b_back(); break;    
		case 0: stop(); b_back(); break;       
	}
}
/**
 *	@function: 赋予步进电机初始状态
 *			初始状态为B相电流倒流
 */
void Motor_Init(){
	b_back();
}
