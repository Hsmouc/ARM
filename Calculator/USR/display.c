#include<hc165.h>
#include<calc.h>
#include<lcd.h>
#include<display.h>
extern unsigned char buf[12];
unsigned char code ascii[]={"0123456789"};
void lcd_display(int num){
	unsigned char arrayLength;
	unsigned char i;
	arrayLength = LongToString(num);
	for(i = 0; i < arrayLength; i++) {
		LcdWrData(ascii[buf[arrayLength-i-1]]); 
	}
}