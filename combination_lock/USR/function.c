#include<reg52.h>
#include<lcd.h>
#include<hc165.h>
#include<keyscan_advance.h>
#include<zlg7290.h>

extern unsigned long num_temp;

void key_function(void) {
	unsigned char key_function;
	key_function = hc165_re();
	Delay1ms(100);
	key_function = hc165_re();
	switch(key_function){
		case 0xfd: clear_step(); break; 
	}
}

void clear_state(void) {
	disp_line(0);
	LcdWrCmd(0x01);
	LcdWrCmd(0x80);
	key_press = 0;
	num_temp = 0;
}