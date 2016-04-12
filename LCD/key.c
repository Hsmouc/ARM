#include<reg51.h>
#include<key.h>
#include<hc165.h>
#include<lcd.h>
unsigned char flag;
extern unsigned char flash;
extern char position;
extern int data time[6];
unsigned char mode = 1;
unsigned char clearFlag = 1;
unsigned char startFlag = 1; 
void keyControl(void) {
	flag = hc165_re();
	Delay1ms(100);
	flag = hc165_re();
	if(flag == 0xfe) {
		mode = 0;
	}
	if(flag == 0xfd) {
		if(startFlag == 0)
			startFlag = 1;
		else
			startFlag = 0; 
	}
	if(flag == 0xfb) {
		flash = 1;
		clearFlag = 0;
	}				 
	if(flag == 0x7f) {
		flash = 0;
		position = 0;
		mode = 1;
	}
	if(flag == 0xf7) {
		Delay1ms(100);
		position = position - 1;
		if(position < 0)
			position = 13;
	}
	if(flag == 0xef) {
		Delay1ms(100);


		position = position + 1;
		if(position > 13)
			position = 0;
	}		 
	if(flag == 0xdf && flash == 1) {
		Delay1ms(100);
		if(position == 0) {
			if(time[0]/1000 > 8)
				time[0] = 0;	
			else
				time[0] += 1000;		 			
		}
		if(position == 1) {
			if(time[0]/100%10 > 8)
				time[0] = 0;
			else
				time[0] += 100; 
		}
		if(position == 2) {
			if(time[0]/10%10 > 8)
				time[0] = 0;
			else
				time[0] += 10; 
		}
		if(position == 3) {
			if(time[0]%10 > 8)
				time[0] = 0;
			else
				time[0] += 1; 
		}
		if(position == 4) {
			if(time[1]/10%10 > 0)
				time[1] = 0;
			else
				time[1] += 10; 
		}
		if(position == 5) {
			if(time[1]%10 > 8)
				time[1] = 0;
			else
				time[1] += 1; 
		}
		if(position == 6) {
			if(time[2]/10 > 2)
				time[2] = 0;
			else
				time[2] += 10; 
		}
		if(position == 7) {
			if(time[2]%10 > 8)
				time[2] = 0;
			else
				time[2] += 1; 
		}
		if(position == 8) {
			if(time[3]/10 > 1)
				time[3] = 0;
			else
				time[3] += 10; 
		}
		if(position == 9) {
			if(time[3]%10 > 8)
				time[3] = 0;
			else
				time[3] += 1; 
		}
		if(position == 10) {
			if(time[4]/10 > 4)
				time[4] = 0;
			else
				time[4] += 10; 
		}
		if(position == 11) {
			if(time[4]%10 > 8)
				time[4] = 0;
			else
				time[4] += 1;				
		}
		if(position == 12) {
			if(time[5]/10 > 4)
				time[5] = 0;
			else
				time[5] += 10; 
		}
		if(position == 13) {
			if(time[5]%10 > 8)
				time[5] = 0;
			else
				time[5] += 1;				
		}
					
	}
	if(flag == 0xbf && flash == 1) {
		Delay1ms(100);
		if(position == 0) {
			if(time[0]/1000 < 1)
				time[0] = 0;	
			else
				time[0] -= 1000;		 			
		}
		if(position == 1) {
			if(time[0]/100%10 < 1)
				time[0] = 0;
			else
				time[0] -= 100; 
		}
		if(position == 2) {
			if(time[0]/10%10 < 1)
				time[0] = 0;
			else
				time[0] -= 10; 
		}
		if(position == 3) {
			if(time[0]%10 < 1)
				time[0] = 0;
			else
				time[0] -= 1; 
		}
		if(position == 4) {
			if(time[1]/10%10 < 1)
				time[1] = 0;
			else
				time[1] -= 10; 
		}
		if(position == 5) {
			if(time[1]%10 < 1)
				time[1] = 0;
			else
				time[1] -= 1; 
		}
		if(position == 6) {
			if(time[2]/10 < 1)
				time[2] = 0;
			else
				time[2] -= 10; 
		}
		if(position == 7) {
			if(time[2]%10 < 1)
				time[2] = 0;
			else
				time[2] -= 1; 
		}
		if(position == 8) {
			if(time[3]/10 < 1)
				time[3] = 0;
			else
				time[3] -= 10; 
		}
		if(position == 9) {
			if(time[3]%10 < 1)
				time[3] = 0;
			else
				time[3] -= 1; 
		}
		if(position == 10) {
			if(time[4]/10 < 1)
				time[4] = 0;
			else
				time[4] -= 10; 
		}
		if(position == 11) {
			if(time[4]%10 < 1)
				time[4] = 0;
			else
				time[4] -= 1;				
		}
		if(position == 12) {
			if(time[5]/10 < 1)
				time[5] = 0;
			else
				time[5] -= 10; 
		}
		if(position == 13) {
			if(time[5]%10 < 1)
				time[5] = 0;
			else
				time[5] -= 1;				
		}
					
	}

}

