#include<reg52.h>
#include<lcd.h>
#include<hc165.h>
#include<keyscan_basic.h>

extern unsigned char step;
int keyscan_transfer(unsigned char key) {
	switch(key) {
		case 0x01:return 1; 
		case 0x02:return 2;
		case 0x03:return 3;
		case 0x04:step = 1; return 10;
		case 0x05:return 4;
		case 0x06:return 5;
		case 0x07:return 6;
		case 0x08:step = 1;return 11;
		case 0x09:return 7;
		case 0x10:return 8;
		case 0x11:return 9;
		case 0x12:step = 1; return 12;
		case 0x13:return 0;
		case 0x16:; step = 1; return 13;
		default: return 0;
	}	
}
