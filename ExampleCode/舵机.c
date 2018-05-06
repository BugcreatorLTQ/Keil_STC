#include <reg51.h>
void InitTimer0(void)
{
    TMOD = 0x01;
    TH0 = 0x0B1;
    TL0 = 0x0E0;
    EA = 1;
    ET0 = 1;
    TR0 = 1;
}
void delay(void)  //通过更改此处程序来控制舵机的角度
{
    unsigned char a,b,c;
    for(c=1;c>0;c--)
        for(b=142;b>0;b--)
            for(a=2;a>0;a--);
}
void main(void)
{
    InitTimer0();
    P1_2=0;
    while(1);
}
void Timer0Interrupt(void) interrupt 1        //设定20ms的周期
{
    
    TH0 = 0x0B1;
    TL0 = 0x0E0;
    P1_2=1;
    delay();
    P1_2=0;
}   
