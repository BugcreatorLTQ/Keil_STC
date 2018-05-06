#include<reg51.h>

sbit PWM=P1^2;


void inittimer0(void)
{
	TMOD=0x01;
	TH0=0x0B1;
	EA=1;
	ET0=1;
	TR0=1;
}

void delay(void)
{
	unsigned char a,b,c;
	for(c=1;c>0;c--)
		for(b=150;b>0;b--)
			for(a=2;a>0;a--);
}

void main(void)      
{
	inittimer0();
	PWM=0;
	while(1);
}

void timer0interrupt(void) interrupt 1
{
	TH0=0X0B1;//
	TL0=0X0E0;
	PWM=1;
	delay();
	PWM=0;
}

