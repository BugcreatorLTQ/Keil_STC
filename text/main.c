#include <reg52.h>
typedef unsigned int uint;
typedef unsigned char uchar;
#define S1  P3 ^ 2	//
sbit R1 = P1 ^ 1; //	right	+
sbit R2 = P1 ^ 0; //	right	-
sbit L1 = P1 ^ 2; //	left	+
sbit L2 = P1 ^ 3; //	left	-
//Sensor Bleak-1
sbit Sen_L = P1 ^ 5; //	sensor left
sbit Sen_R = P1 ^ 4; //	sensor right
sbit pwm1 = P0 ^ 1;  //输出PWM信号
sbit pwm2 = P0 ^ 3;
uint pwm_value = 1500; //初值为1.5ms
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
    TMOD = 0x11;        //开定时器0,1
    TH0 = -20000 / 256; //定时20MS,20MS为一个周期
    TL0 = -20000 % 256;
    TH1 = -1500 / 256; //定时1.5MS,这时舵机处于0度
    TL1 = -1500 % 256;
    EA = 1;  //开总断
    TR0 = 1; //开定时器0
    ET0 = 1;
    TR1 = 1; //开定时器1
    ET1 = 1;
}

void timer0(void) interrupt 1 //定时器0中断函数
{
    switch (flag)
    {
    case 1:
        pwm1 = 1;
        break;
    case 2:
        pwm2 = 1;
        break;
    }
    TH0 = -20000 / 256;
    TL0 = -20000 % 256;
    TR1 = 1;
}

void timer1(void) interrupt 3 //定时器1中断函数
{
    switch (flag)
    {
    case 1:
        pwm1 = 0;
        break;
    case 2:
        pwm2 = 0;
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
        switch (type)
        {
        case 1:
            pwm_value = 2500;
            break;
        case 2:
            pwm_value = 2250;
            break;
        case 3:
            pwm_value = 2000;
            break;
        case 4:
            pwm_value = 1750;
            break;
        case 5:
            pwm_value = 1500;
            break;
        case 6:
            pwm_value = 1250;
            break;
        case 7:
            pwm_value = 1000;
            break;
        case 8:
            pwm_value = 750;
            break;
        case 9:
            pwm_value = 500;
            break;
        }
        delay_ms(1000);
    }
}

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
    P2 = ~1;
}
void TurnLeft()
{
    R1 = 0;
    L1 = 1;
    R2 = 1;
    L2 = 0;
    P2 = ~2;
}
void TurnRight()
{
    R1 = 1;
    R2 = 0;
    L1 = 0;
    L2 = 1;
    P2 = ~4;
}
void Down()
{
    R1 = 1;
    R2 = 0;
    L1 = 1;
    L2 = 0;
    P2 = ~8;
}
void CarStop()
{
    R1 = 1;
    R2 = 1;
    L1 = 1;
    L2 = 1;
    P2 = ~16;
}

void main(void) //主函数
{
    InitTimer();
    pwm_value = 1500;
    flag = 0;
    flag = 2;
    Stop(5); //UD舵机D位(45)
    flag = 1;
    Stop(8); //LR舵机M位
    CarStop();
    while (1)
    {
	if(S1==1){
		P2=~32;
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
	else if(S1==0){
		P2=~64;
        flag = 1;
        Stop(5); //LR舵机R位
        flag = 2;
        Stop(4); //UD舵机D位
        flag = 2;
        Stop(7); //UD舵机U位
        flag = 1;
        Stop(8); //LR舵机M位
        flag = 2;
        Stop(5); //UD舵机D位(45)
        flag = 2;
        Stop(7); //UD舵机U位
		}
    }
}
