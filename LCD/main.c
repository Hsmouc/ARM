#include<reg52.h>
#include<lcd.h>
#include<hc165.h>
#include<clock.h>
#include<key.h>

extern unsigned char j;
extern clockTypeDef clock;
extern unsigned char mode;
extern int data second[3];
extern unsigned char clearFlag;
extern unsigned char startFlag;
void main(){
	TH0 = 0xd8;
	TL0 = 0xf0;
	TMOD = 0x01;
	ET0 = 1;
	TR0 = 1;
	EA = 1;
	hc165_init();
	LcdInit();
	while(1){
		if(mode == 0)
			second_display();
		else
			time_display();
		keyControl();	
	}	
}

 void time_int0(void) interrupt 1 {
 	unsigned char i;
	ET0 = 0;
	TR0 = 0;
	TH0 = 0xd8;//0x3c;
	TL0 = 0xf0;//0xb0;
	TR0 = 1;
	timeCalc();
	if(mode == 0 && startFlag == 0)
		secondCalc();
	if(mode == 0 && clearFlag == 0) {
		for(i = 0; i < 3; i++){
			second[i] = 0;
		}
		startFlag = 1;
		clearFlag = 1;
	}
	j = j + 1;
	ET0 = 1; 
}

