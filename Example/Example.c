#include <reg52.h>
typedef unsigned int uint;
typedef unsigned char uchar;
sbit K = P0 ^ 7;	
sbit pwm1 = P0 ^ 5;  //???PWM?z?
sbit pwm2 = P0 ^ 3;
uint pwm_value = 1500; //????1.5ms
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
    TMOD = 0x11;        //???????0,1
    TH0 = -20000 / 256; //???20MS,20MS?h??????
    TL0 = -20000 % 256;
    TH1 = -1500 / 256; //???1.5MS,??????????0??
    TL1 = -1500 % 256;
    EA = 1;  //?????
    TR0 = 1; //???????0
    ET0 = 1;
    TR1 = 1; //???????1
    ET1 = 1;
}

void timer0(void) interrupt 1 //?????0??????
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
    }
    TH0 = -20000 / 256;
    TL0 = -20000 % 256;
    TR1 = 1;
}

void timer1(void) interrupt 3 //?????1??????
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

void GetBall()
{ 	 
    flag = 1;
	P2=~4;
    Stop(5); //LR???R?
    flag = 2;
	P2=~8;
    Stop(4); //UD???D?
    flag = 2;
	P2=~16;
    Stop(7); //UD???U?
    flag = 1;
	P2=~32;
    Stop(8); //LR???M?
    flag = 2;
	P2=~64;
    Stop(5); //UD???D?(45)
    flag = 2;
	P2=~128;
    Stop(7); //UD???U?
}


void main(void) //??????
{				
	unsigned char i;
	delay_ms(500);
    InitTimer();	 
    pwm_value = 1500; 
	flag=3;
    while (1)
    {
		for(i=5;i<8;i++){
			P2=~(1<<(i-1));
			Stop(i);	  
			delay_ms(5000);
		}
    }
}
