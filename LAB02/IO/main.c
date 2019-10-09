/*
* @time: 2019-10-9 
* @author: Jeremy.Zhang, George
* @function: IO Parallel Control
*/

#include "STC12C5A60S2.h"


/* content: which one is 1(ʵ������: ��Ӧ��ʵ��������Ϊ1) */
#define IO_EXP1  0      //����KEY1, ��һλ����ܴ�0~9������ʾ
#define IO_EXP2  1      //����KEY2, �л�ģʽ������KEY1����ܴ�0~9������ʾ���������з������ķ���


/* redefine data type(�ض����������ͱ���) */
typedef unsigned char u8;


/* define all pins and variable(�����������źͱ���) */
unsigned char NUMS[11] = {0x03, 0x9F, 0x25, 0x0D, 0x99, 0x49, 0x41, 0x1F, 0x01, 0x09, 0xff};    //�����б�(���һλ���)
sbit KEY1 = P3^2;      //KEY1����
sbit KEY2 = P3^4;	   //KEY2����
sbit BEEP = P1^0;      //����������(�͵�ƽ��Ч) 


/* define Eight-Segment pins, Low-Level works(����˶����������, �͵�ƽ��Ч)*/
sbit SM_G1 = P2^0;  
sbit SM_G2 = P2^1;
sbit SM_G3 = P2^2;
sbit SM_G4 = P2^3;


/*
* @function: choose_SM, ������һ���������ʾ
* @args: index: ��������; status: �͵�ƽ��Ч
* @return: None
*/
void choose_SM(u8 index, u8 status)
{
	switch (index)
	{
		case 1:
			SM_G1 = status;
			break;
		case 2:
			SM_G2 = status;
			break;
		case 3:
			SM_G3 = status;
			break;
		case 4:
			SM_G4 = status;
			break;
		default:
			break;
	}
}


/*
* @function: delay_by_2ms, ��ʱ����, 2ms�Ļ�
* @args: time: ʱ��
* @return: None
*/
void delay_by_2ms(unsigned long int time)
{
	unsigned long int i;
	for (i = 0; i < time * 100; i++);
}



#if IO_EXP1

void main()
{
	/* define nums index variable(����������������) */
	u8 n_index;
	while (1)
	{
		if (0 == KEY1)
		{
			choose_SM(1, 0);
			for (n_index = 0; n_index <= 9; n_index++)
			{
				/* display nums and delay 1s(��ʾ����, ����ʱ1��) */
				P0 = NUMS[n_index];
				delay_by_2ms(500);
			}
			/* clear diaplay nums(�����ʾ����) */
			P0 = NUMS[n_index];
		}
	}		
}

#endif


#if IO_EXP2

void main()
{
	/* define nums index and Eight-Segment index variable(�������ֺ��������������) */
	u8 n_index = 0, s_index = 1;

	/* config Beeper Mode and default choose Eight-Segment 1(���÷�����Ϊ�������ģʽ, Ĭ��ѡ�������1) */
	P1M0 = 0x01;
	choose_SM(1, 0);	

	while (1)
	{
		if (0 == KEY2)
		{
			/* request to limit range 1-4, setting Eight-Segment mode(���Ʒ�Χ��1-4, ѭ��ѡ��, ͬʱ������ʾ����һ���͵�ǰ������ܵ�ģʽ, ) */
			s_index++;
			if (s_index < 5)
			{
				choose_SM(s_index - 1, 1);
				choose_SM(s_index, 0);
			}
			else
			{
				s_index = 1;
				choose_SM(1, 0);
				choose_SM(4, 1);
			}
		}

		if (0 == KEY1)
		{
			for (n_index = 0; n_index <= 9; n_index++)
			{
				/* display nums and delay 1s with beeper(��ʾ����, ����ʱ1��, ͬʱ�������������) */
				P0 = NUMS[n_index];
				BEEP = 0;
				delay_by_2ms(250);
				BEEP = 1;
				delay_by_2ms(250);
			}
			/* clear diaplay nums(�����ʾ����) */
			P0 = NUMS[n_index];	
		}
	}
}

#endif
