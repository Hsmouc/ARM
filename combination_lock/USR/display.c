#include<reg52.h>
#include<display.h>
#include<process.h>
#include<lcd.h>
extern unsigned char buf[12];
unsigned char code ascii[]={"0123456789"};
void lcd_numdisplay(unsigned long num){
	unsigned char arrayLength;
	unsigned char i;
	arrayLength = LongToString(num);
	for(i = 0; i < arrayLength; i++) {
			LcdWrData(ascii[buf[arrayLength-i-1]]); 
	}
}

void password_display(unsigned long num) {
	unsigned char arrayLength;
	unsigned char i;
	arrayLength = LongToString(num);
	for(i = 0; i < arrayLength; i++) {
		LcdWrData('*');
	}
}
