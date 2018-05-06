 #include<reg51.h>
void delay500us(void)   //Îó²î 0us
{
    unsigned char a,b;
    for(b=71;b>0;b--)
        for(a=2;a>0;a--);
}
void delay1ms(void)   //Îó²î 0us
{
    unsigned char a,b,c;
    for(c=1;c>0;c--)
        for(b=142;b>0;b--)
            for(a=2;a>0;a--);
}
void L0(void)
{
int a,b;
	for(a=49;a>0;a--)
	{	PWM=0;
		for(b=19;b>0;b--)
		delay1ms();
		delay500us();
		PWM=1;
		delay500us();
	} }
void SW0(void)
{
	int a,b;
	for(a=49;a>0;a--)
	{	PWM=0;
		for(b=19;b>0;b--)
		delay1ms();
		PWM=1;
		delay1ms();
	
	 }}

void JL0(void)
{
	int a,b;
	for(a=49;a>0;a--)
	{	PWM=0;
		for(b=18;b>0;b--)
		delay1ms();
		delay500us();
		PWM=1;
		delay1ms();
		delay500us();
	
	 }}
void YSW0(void)
{
	int a,b;
	for(a=49;a>0;a--)
	{	PWM=0;
		for(b=18;b>0;b--)
		delay1ms();
		PWM=1;
		delay1ms();
		delay1ms();
	
	
	 }}

void YBL0(void)
{
	int a,b;
	for(a=49;a>0;a--)
	{	PWM=0;
		for(b=17;b>0;b--)
		delay1ms();
		delay500us();
		PWM=1;
		delay1ms();
		delay1ms();
		delay500us();
	
	
	 }}





