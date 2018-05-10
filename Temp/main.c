#include <reg52.h>
typedef unsigned int uint;
typedef unsigned char uchar;
sbit Sen_R = P1^4;
sbit Sen_L = P1^5;


void main(void) //Ö÷º¯Êı
{				  	 
	if(Sen_R==0 && Sen_L==0)
		P2=~1;
	else if(Sen_R==0&&Sen_L==1)
		P2=~2;
	else if(Sen_R==1&&Sen_L==0)
		P2=~4;
	else 
		P2=~8;
	
}
