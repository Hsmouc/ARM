#include<hc165.h>
#include<calc.h>
#include<lcd.h>
#include<display.h>
extern unsigned char buf[12];
unsigned char code ascii[]={"0123456789"};
extern int temp;
extern unsigned char step;
int lcd_numdisplay(int num){
	unsigned char arrayLength;
	unsigned char i;
	arrayLength = LongToString(num);
	for(i = 0; i < arrayLength; i++) {
		if(step == 0 || step == 2 || step == 3)
			LcdWrData(ascii[buf[arrayLength-i-1]]); 
	}
	return arrayLength;
}

void lcd_flagdisplay(int num) {
	switch(num) {
		case 10: LcdWrData('+'); break;
		case 11: LcdWrData('-'); break;
		case 12: LcdWrData('*'); break;
	}
	step = 2;
}