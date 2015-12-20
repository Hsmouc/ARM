#include<reg51.h>
sbit BEEP = P1^5;
volatile unsigned char k1 = 50;
void Interrupt_T0(void) interrupt 1
{
	k1--;
	TH0 = 0xB8;
	TL0 = 0x00;
}
void main(void)
{
	unsigned char cnt = 0;
    BEEP = 0;
	TMOD = 0x01;
	TH0 = 0xB8;
	TL0 = 0x00;
	TR0 = 1;
    while (1){
        if (TF0 == 1){  
            TF0 = 0;  
            TH0 = 0xB8;
            TL0 = 0x00;
            cnt++; 
            if (cnt >= 50){ 
                cnt = 0; 
               	BEEP  = ~BEEP;
            }
        }
    }
}
