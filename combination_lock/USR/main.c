#include<reg52.h>
#include<process.h>
#include<keyscan.h>
#include<display.h>
#include<I2C.h>
#include<hc165.h>
#include<lcd.h>
#include<ZLG7290.h>
void main() {
	unsigned long inputTransfered = 0; 
	int input = 0;
	key_press = 0;
	hc165_init();
	I2C_Init();
	LcdInit();
	while(1){
		Read_ZLG7290Key();
		delayMS(200);
		if(key_press == 1){
			key_press = 0;
			input = key_transfer(key_code);
			inputTransfered = number_transfer(input);
			disp_line(0);
			password_display(inputTransfered);
			if(inputTransfered == 123456) {
				disp_line(1);
				LcdWrData('O');
				LcdWrData('K');
			}
		}
	}
}