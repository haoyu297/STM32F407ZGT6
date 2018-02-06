#ifndef __USER_ADC_H
#define __USER_ADC_H	

typedef unsigned int  u32;
typedef unsigned short  u16;
typedef unsigned char   u8;

//////////////////////////////////////////////////////////////////////////////////	 
 							   
void  ADC1_Init(void); 				//ADC通道初始化
u16  Get_Adc(u8 ch); 				//获得某个通道值 
 
#endif 















