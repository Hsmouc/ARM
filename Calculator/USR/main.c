#include<reg52.h>
#include<lcd.h>
#include<hc165.h>
#include<display.h>
#include<calc.h>
#include<I2C.h>
#include<zlg7290.h>
#include<keyscan_basic.h>
#include<keyscan_advance.h>
int tempKeytransfer_1 = 0;
int tempNumtransfer_1 = 0;
int tempKeytransfer_2 = 0;
int tempNumtransfer_2 = 0;
int tempKeytransfer_3 = 0;
int tempNumtransfer_3 = 0;
int tempKeytransfer_4 = 0;
int tempNumtransfer_4 = 0;
int resultTransfer;
int result = 0;
int decimal_result = 0;
unsigned char decimalFlag_1 = 0;
unsigned char decimalFlag_2 = 0;
unsigned char step = 0;
int temp_useless;
int temp_decimal_useless;
int temp;
int temp_decimal;
extern int num_temp;
extern int dec_temp;
extern unsigned char state;
void main(){
	unsigned char tempKeycode;
	hc165_init();
	I2C_Init();
	LcdInit();
	while(1){
		Read_ZLG7290Key();
		delayMS(200);
		key_function();
		if(key_press == 1 && step == 0 && state == 0) {
			key_press = 0;
			tempKeytransfer_1 = keyscan_transfer(key_code);
			if(key_code != 0x04 && key_code != 0x08 && key_code != 0x0C && key_code != 0x10 && key_code != 0x0E) {
				tempNumtransfer_1 = number_transfer(tempKeytransfer_1);
				disp_line(0);
				temp = lcd_numdisplay(tempNumtransfer_1);
			}
			LcdWrCmd(0x80+temp);
		}

		if(key_press == 1 && step == 0 && state == 1){
			key_press = 0;
			LcdWrCmd(0x80+temp);
			decimal_display();
			tempKeytransfer_3 = keyscan_transfer(key_code);
			if(key_code != 0x04 && key_code != 0x08 && key_code != 0x0C && key_code != 0x10 && key_code != 0x0E) {
				tempNumtransfer_3 = decimal_transfer(tempKeytransfer_3);
				temp_decimal = lcd_numdisplay(tempNumtransfer_3) + 1;	
			}
			LcdWrCmd(0x80+temp+temp_decimal);
			decimalFlag_1 = 1;
		}

		if(key_press == 1 && step == 1) {
			key_press = 0;
			tempKeycode = key_code;
			lcd_flagdisplay(keyscan_transfer(key_code));
			num_temp = 0;
			dec_temp = 0;
			state = 0;
		}

		if(key_press == 1 && step == 2 && state == 0) {
			key_press = 0;
			LcdWrCmd(0x80+temp+temp_decimal+1);
			tempKeytransfer_2 = keyscan_transfer(key_code);
			if(key_code != 0x0F && key_code != 0x0E){
				tempNumtransfer_2 = number_transfer(tempKeytransfer_2);
				temp_useless = lcd_numdisplay(tempNumtransfer_2);
			}
			LcdWrCmd(0x80+temp+temp_decimal+temp_useless+1);
			decimalFlag_2 = 1;
		}

		if(key_press == 1 && step == 2 && state == 1){
			key_press = 0;
			LcdWrCmd(0x80+temp+temp_decimal+temp_useless+1);
			decimal_display();
			tempKeytransfer_4 = keyscan_transfer(key_code);
			if(key_code != 0x0F && key_code != 0x0E) {
				tempNumtransfer_4 = decimal_transfer(tempKeytransfer_4);
				temp_decimal_useless = lcd_numdisplay(tempNumtransfer_4);	
			}
		}

		if(step == 3){	
			if(decimalFlag_1 * decimalFlag_2 == 0) {
				result = number_calculate(tempNumtransfer_1,tempNumtransfer_2,tempKeycode);
				disp_line(1);
				temp_useless = lcd_numdisplay(result);	
		 	}
			if(decimalFlag_1 * decimalFlag_2 == 1) {
				result = number_calculate(tempNumtransfer_1,tempNumtransfer_2,tempKeycode);
				decimal_result = number_calculate(tempNumtransfer_3,tempNumtransfer_4,tempKeycode);
				disp_line(1);
				if(decimal_result > 9) {
					temp = lcd_numdisplay(result+1);
					LcdWrCmd(0x80+0x40+temp);
					decimal_display();
					LcdWrCmd(0x80+0x40+temp+1);
					temp_useless = lcd_numdisplay(decimal_result%10);
				}
				else {
					temp = lcd_numdisplay(result);
					LcdWrCmd(0x80+0x40+temp);
					decimal_display();
					LcdWrCmd(0x80+0x40+temp+1);
					temp_useless = lcd_numdisplay(decimal_result);
				}
			}
		}
	}
}
