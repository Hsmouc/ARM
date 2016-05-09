#include<hc165.h>
#include<calc.h>
#include<lcd.h>

void lcd_display(int num){
	unsigned char *displayArray;
	unsigned char arrayLength;
	unsigned int i;
	arrayLength = LongToString(*displayArray,num);
	for(i = 0; i < arrayLength; i++) {
		LcdWrData(*displayArray);
		displayArray++;
	}
}