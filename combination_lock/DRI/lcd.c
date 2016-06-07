#include<reg52.h>
sbit LCD_E = P2^2;
sbit LCD_RW = P2^1;
sbit LCD_RS = P2^0;
sbit HC164_SDAT = P2^3;
sbit HC164_SCLK = P2^4;
void send_data(unsigned char dat) {
	unsigned char i;
	for(i = 0; i < 8; i++){
		HC164_SCLK = 0;
		if(dat & 0x80){
			HC164_SDAT = 1;
		}
		else{
			HC164_SDAT = 0;
		}
		HC164_SCLK = 1;
		dat = dat << 1;
	}
}

void Delay1ms(unsigned int c) {
	unsigned char a,b;
	for(; c>0; c--) {
		for(b = 199; b > 0; b--) {
			for(a = 1; a > 0; a--);
		}
	}
}

void LcdWrCmd(unsigned char com) {
	unsigned char x;
	LCD_E = 0;
	LCD_RS = 0;
	LCD_RW = 0;
	
	send_data(com);
	x++;
	LCD_E = 1;
	x++;
	LCD_E = 0;
	Delay1ms(1);
}
void LcdWrData(unsigned char dat) {
	unsigned char x;
	LCD_E = 0;
	LCD_RS = 1;
	LCD_RW = 0;

	send_data(dat);
	x++;
	LCD_E = 1;
	x++;
	LCD_E = 0;
	Delay1ms(1);
}

void disp_line(unsigned char line) {
	if(line == 0){
		LcdWrCmd(0x80 + 0x00);
	}
	else{
		LcdWrCmd(0x80 + 0x40);
	}
}

void LcdInit(){
	LcdWrCmd(0x38);
	LcdWrCmd(0x0c);
	LcdWrCmd(0x06);
	LcdWrCmd(0x01);
}