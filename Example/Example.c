#include<reg52.h>
							
sbit S1=P2^0;	//¹âµç

void main()
{		 
	while(1){	
		if(S1==1)
			P2=~1;
		else if(S1==0)
			P2=~2;
		else
			P2=~4;		
	}
}					
