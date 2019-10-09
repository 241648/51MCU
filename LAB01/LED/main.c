/*
* @time: 2019-10-9 
* @author: Jeremy.Zhang
* @function: LED and Beeper blink(LED��˸�ͷ�������)
*/

#include "STC12C5A60S2.h"

/* define all pins(������������) */
sbit LED1 = P2^4;    //high(1) works(�ߵ�ƽ����)   
sbit LED2 = P2^5;    //high(1) works(�ߵ�ƽ����) 
sbit LED3 = P2^6;	 //high(1) works(�ߵ�ƽ����) 
sbit LED4 = P2^7;  	 //high(1) works(�ߵ�ƽ����) 
sbit BEEP = P1^0;    //low(0)  works(�͵�ƽ����)


void main()
{	
	/* define delay variable(������ʱ����) */
	unsigned long int i;
	
	/* config Beeper Mode(���÷�����Ϊ�������ģʽ) */
	P1M0 = 0x01;	

	while(1)
	{
		for(i=0;i<50000;i++);
		BEEP = 0;
		LED1 = 0;
		LED2 = 1;
		LED3 = 1;
		LED4 = 1;

		for(i=0;i<50000;i++);
		BEEP = 1;
		LED1 = 0;
		LED2 = 0;
		LED3 = 1;
		LED4 = 1;

		for(i=0;i<50000;i++);
		BEEP = 0;
		LED1 = 0;
		LED2 = 0;
		LED3 = 0;
		LED4 = 1;

		for(i=0;i<50000;i++);
		BEEP = 1;
		LED1 = 0;
		LED2 = 0;
		LED3 = 0;
		LED4 = 0;
	}	
}
