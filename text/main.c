#include <reg52.h>
typedef unsigned int uint;
typedef unsigned char uchar;
/*
sbit R1 = P1 ^ 1; //	right	+
sbit R2 = P1 ^ 0; //	right	-
sbit L1 = P1 ^ 2; //	left	+
sbit L2 = P1 ^ 3; //	left	-
//Sensor Bleak-1
sbit Sen_L = P1 ^ 5; //	sensor left
sbit Sen_R = P1 ^ 4; //	sensor right
*/
sbit K=P0 ^ 7;
sbit S1 = P0^1;	
sbit pwm1 = P0 ^ 5;  //���PWM�ź�
sbit pwm2 = P0 ^ 3;
uint pwm_value = 1500; //��ֵΪ1.5ms
uchar flag = 0;        //Flag

void delay_ms(uint x)
{
    uint i;
    while (x--)
        for (i = 0; i < 125; i++)
            ;
}

void InitTimer(void)
{
    TMOD = 0x11;        //����ʱ��0,1
    TH0 = -20000 / 256; //��ʱ20MS,20MSΪһ������
    TL0 = -20000 % 256;
    TH1 = -1500 / 256; //��ʱ1.5MS,��ʱ�������0��
    TL1 = -1500 % 256;
    EA = 1;  //���ܶ�
    TR0 = 1; //����ʱ��0
    ET0 = 1;
    TR1 = 1; //����ʱ��1
    ET1 = 1;
}

void timer0(void) interrupt 1 //��ʱ��0�жϺ���
{
    switch (flag)
    {
    case 1:
        pwm1 = 1;
        break;
    case 2:
        pwm2 = 1;
        break;
	case 3:
		K = 1;
		break;
	case 4:
		pwm2=1;
		K=1;
		break;
	case 5:
		pwm1=1;
		K=1;
		break;
    }
    TH0 = -20000 / 256;
    TL0 = -20000 % 256;
    TR1 = 1;
}


void timer1(void) interrupt 3 //��ʱ��1�жϺ���
{
    switch (flag)
    {
    case 1:
        pwm1 = 0;
        break;
    case 2:
        pwm2 = 0;
        break;
	case 3:
		K = 0;
		break;	   
	case 4:
		pwm2=0;
		K=0;
		break;
	case 5:
		pwm1=0;
		K=0;
		break;
    }
    TH1 = -pwm_value / 256;
    TL1 = -pwm_value % 256;
    TR1 = 0;
}

void Stop(unsigned char type)
{
    unsigned char i;
    for (i = 0; i < 5; i++)
    {
		pwm_value=(uint)(2750-250*type);
        delay_ms(1000);
    }
}
/*
void Sleep(unsigned char z)
{
    unsigned char i, j;
    for (i = 0; i < 255; i++)
        for (j = 0; j < 255; j++)
            while (z--)
                ;
}

void Run()
{
    R1 = 0;
    L1 = 0;
    R2 = 1;
    L2 = 1;
    P2 = ~3;
}
void TurnLeft()
{
    R1 = 0;
    L1 = 1;
    R2 = 1;
    L2 = 0;
    P2 = ~5;
}
void TurnRight()
{
    R1 = 1;
    R2 = 0;
    L1 = 0;
    L2 = 1;
    P2 = ~9;
}
void Down()
{
    R1 = 1;
    R2 = 0;
    L1 = 1;
    L2 = 0;
    P2 = ~17;
}
void CarStop()
{
    R1 = 1;
    R2 = 1;
    L1 = 1;
    L2 = 1;
    P2 = ~33;
}
 	 
void Runing()
{
	if (Sen_L == 0 && Sen_R == 0)
		Run();
	else if (Sen_L == 1 && Sen_R == 0)
	    TurnRight();
	else if (Sen_L == 0 && Sen_R == 1)
		TurnLeft();
	else
		Down();
	Sleep(1);	
}
*/
void GetBall()
{ 	 
    flag = 1;
	P2=~4;
    Stop(5); //LR���Rλ
							   
	flag=3;
	Stop(5); //open

    flag = 2;
	P2=~8;
    Stop(4); //UD���Dλ

	//--------------
	flag=3;
	Stop(8); //close

    flag = 4;
	P2=~16;
    Stop(8); //UD���Uλ

    flag = 5;
	P2=~32;
    Stop(8); //LR-M

    flag = 2;
	P2=~64;
    Stop(6); //UD���Dλ(45)
	
	flag=3;
	Stop(5); //open

    flag = 2;
	P2=~128;
    Stop(7); //UD���Uλ
}


void main(void) //������
{		
	delay_ms(500);
    InitTimer();	 
    pwm_value = 1500; 
    flag = 2;
	P2=~1;
    Stop(7); //UD���Uλ(45)
    flag = 1;
	P2=~2;
    Stop(8); //LR���Mλ
	P2=~4;	
	flag=3;
	Stop(7);	//open
    while (1)
    {
		if(S1==0)
			GetBall();
		else
			P2=~3;
    }
}
