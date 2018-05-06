#include<reg52.h>
							
sbit S1=P0^1;	//¹âµç
						
void Sleep(unsigned char z)
{
	unsigned char i,j;
	while(z--)
		for(i=0;i<255;i++)
			for(j=0;j<255;j++);
}

void main()
{		 
	while(1){	
		if(S1==1)
			P2=~1;
		else if(S1==0)
			P2=~4;
		else
			P2=~0;
	}
}					
