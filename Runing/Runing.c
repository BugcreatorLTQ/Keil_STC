#include<reg52.h>
							
sbit R2=P1^0;	//	right	-
sbit R1=P1^1;	//	right	+
sbit L2=P1^2;	//	left	-			  
sbit L1=P1^3;	//	left	+
//Sensor Bleak-1
sbit Sen_L=P1^5;//	sensor left
sbit Sen_R=P1^6;//	sensor right
sbit S1=P0^1;	//	1-no Obstacles

void Sleep()
{
	unsigned char i,j;
	for(i=0;i<255;i++)
	for(j=0;j<255;j++) ;
}

void Run()
{
	R1=0;
	L1=0; 
	R2=1;
	L2=1;
	P2=~1;
	Sleep();

}
void TurnLeft()
{
	R1=0;
	L1=1;																																					  
	R2=1;
	L2=0;
	P2=~2;
	Sleep();
}
void TurnRight()
{
	R1=1;
	R2=0;
	L1=0;
	L2=1;
	P2=~4;
	Sleep();
}
void Down()
{
	R1=1;
	R2=0;
	L1=1;
	L2=0; 
	P2=~8;
	Sleep();
}	   
void Stop()
{
	R1=1;
	R2=1;
	L1=1;
	L2=1;
	P2=~16;
	Sleep();
}  
	 
void Runing(unsigned char type)
{		      
	//type=1 black

	if(Sen_L==0&&Sen_R==0)
		Run();
	else if(Sen_R==0&&Sen_L==1)
		TurnLeft();
	else if(Sen_R==1&&Sen_L==0)
		TurnRight();
	else if(Sen_R==1&&Sen_L==1)
		Down();
}

void main()
{		 
	Stop();
	while(1){
		if(S1==1)
			Runing();
		else
			Stop();
		Sleep();
	}
}					
