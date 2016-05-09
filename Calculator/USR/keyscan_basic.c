#include<reg52.h>
#include<lcd.h>
#include<hc165.h>
#include<keyscan_basic.h>

extern unsigned char step;
int keyscan_transfer(unsigned char key) {
	int key_transfer;
	switch(key) {
		case 0x80:key_transfer = 1; 
	}
	if(key_transfer == '+' ) {
		step = 1;
	}
	return key_transfer;	
}
