#include<reg52.h>
#include<lcd.h>
#include<hc165.h>
#include<keyscan_advance.h>
#include<zlg7290.h>
extern int tempNumtransfer_1;
extern int tempNumtransfer_2;
extern int tempKeytransfer_1;
extern int tempKeytransfer_2;
extern unsigned char step;
extern unsigned char result;
extern int num_temp;
void key_function(void) {
	unsigned char key_function;
	key_function = hc165_re();
	Delay1ms(100);
	key_function = hc165_re();
	switch(key_function){
		case 0xfd: clear_step(); break; 
	}
}

void clear_step(void) {
	tempNumtransfer_1 = 0;
	tempNumtransfer_2 = 0;
	tempKeytransfer_1 = 0;
  	tempKeytransfer_2 = 0;
	step = 0;
	disp_line(0);
	LcdWrCmd(0x01);
	LcdWrCmd(0x80);
	key_press = 0;
	num_temp = 0;
}