#include<reg51.h>
#define NUM_MAX 65535
unsigned char dis_num[10]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
unsigned char code1[5]={0xf7,0xef,0xdf,0xbf,0x7f};
void delay1ms(int t)
{
   int i,j;
   for(i=0;i<t;i++)
      for(j=0;j<120;j++);
}

void main(void)
{
   int j,k=1,a[5]; 
   TMOD=0x01;
   TH1=0x50;
   TL1=0xb0;
   TR1=0x01;
   ET1=1;
   while(1)
   {
      if(P3==0xdf)
	  {
	     delay1ms(200);
         k++;
	   }
      if(k>NUM_MAX)
	     k=1;
	  a[0]=k/10000;
	  a[1]=(k/1000)%10;
	  a[2]=(k/100)%10;
	  a[3]=(k/10)%10;
	  a[4]=k%10;
	     for(j=0;j<5;j++)
		 {
		    P0=dis_num[a[j]];
			P2=code1[j];
			delay1ms(1);
			P2=0xff;
	     }
   }
}