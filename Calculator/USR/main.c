#include<reg52.h>
#include<lcd.h>
#include<hc165.h>
#include<display.h>
#include<calc.h>
#include<I2C.h>
#include<zlg7290.h>
#include<keyscan_basic.h>

void main(){
	hc165_init();
	I2C_Init();
	LcdInit();
	while(1){
		int tempNum = 0;
		Read_ZLG7290Key();
		if(key_press == 1) {
			key_press = 0;
			tempNum = number_transfer(key_press);
			}
			disp_line(0);
			lcd_display(tempNum);
	}
}
