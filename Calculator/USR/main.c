#include<reg52.h>
#include<lcd.h>
#include<hc165.h>
#include<display.h>
#include<calc.h>
#include<I2C.h>
#include<zlg7290.h>
#include<keyscan_basic.h>
int tempKeytransfer_1 = 0;
int tempNumtransfer_1 = 0;
int tempKeytransfer_2 = 0;
int tempNumtransfer_2 = 0;
int resultTransfer;
int result = 0;
unsigned char step = 0;
int temp_useless;
int temp;
extern int num_temp;
void main(){
	unsigned char tempKeycode;
	hc165_init();
	I2C_Init();
	LcdInit();
	while(1){
		Read_ZLG7290Key();
		delayMS(300);
		if(key_press == 1 && step == 0) {
			key_press = 0;
			tempKeytransfer_1 = keyscan_transfer(key_code);
			if(key_code != 0x04 && key_code != 0x08 && key_code != 0x0C) {
				tempNumtransfer_1 = number_transfer(tempKeytransfer_1);
				disp_line(0);
				temp = lcd_numdisplay(tempNumtransfer_1);
				LcdWrCmd(0x80+temp);
			}
		}
		if(key_press == 1 && step == 1) {
			key_press = 0;
			tempKeycode = key_code;
			lcd_flagdisplay(keyscan_transfer(key_code));
			num_temp = 0;
		}
		if(key_press == 1 && step == 2) {
			key_press = 0;
			tempKeytransfer_2 = keyscan_transfer(key_code);
			if(key_code != 0x0F){
				tempNumtransfer_2 = number_transfer(tempKeytransfer_2);
				LcdWrCmd(0x80+temp+1);
				temp_useless = lcd_numdisplay(tempNumtransfer_2);
			}
		}
		if(step == 3){	
			result = number_calculate(tempNumtransfer_1,tempNumtransfer_2,tempKeycode);
			disp_line(1);
			temp_useless = lcd_numdisplay(result);	
		}
	}
}
