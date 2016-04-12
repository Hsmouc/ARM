#include<reg52.h>
#include<clock.h>
extern int data second[3];
unsigned char timedisplay[14]={0,0,0,0,0,0,0,0,0,0,0,0,0,0};
sbit LCD_E = P1^2;
sbit LCD_RW = P1^1;
sbit LCD_RS = P1^0;
sbit HC164_SDAT = P1^3;
sbit HC164_SCLK = P1^4;
extern clockTypeDef clock;
char position = 0;
unsigned char flash = 0;
unsigned char j = 0;
unsigned char code ascii[]={"0123456789"};
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
	/*char code year []={0x04,0x0F,0x12,0x0F,0x0A,0x1F,0x02,0x02,};
	char code month []={0x00,0x0F,0x09,0x0F,0x09,0x0F,0x09,0x13,};
	char code day []={0x00,0x1F,0x11,0x11,0x1F,0x11,0x11,0x1F,};
	char code path1 []={0x01,0x02,0x04,0x0A,0x02,0x02,0x02,0x02,};
	char code path2 []={0x1E,0x02,0x1F,0x08,0x1E,0x04,0x1F,0x0A,};
	char code path3 []={0x15,0x1F,0x00,0x1F,0x01,0x1F,0x10,0x1C,};
	char code path4 []={0x0E,0x0A,0x0A,0x0A,0x0A,0x0A,0x0A,0x13,}; */
	LcdWrCmd(0x38);
	LcdWrCmd(0x0c);
	LcdWrCmd(0x06);
	LcdWrCmd(0x01);
	/*Delay1ms(50);
	LcdWrCmd(0x40);
	for(i = 0; i < 8; i++)
		LcdWrData(year [i]);
	for(i = 0; i < 8; i++)
		LcdWrData(month [i]);
	for(i = 0; i < 8; i++)
		LcdWrData(day [i]);
	for(i = 0; i < 8; i++)
		LcdWrData(path1 [i]);
	for(i = 0; i < 8; i++)
		LcdWrData(path2 [i]);
	for(i = 0; i < 8; i++)
		LcdWrData(path3 [i]);
	for(i = 0; i < 8; i++)
		LcdWrData(path4 [i]);*/
}
void second_display() {
	LcdWrCmd(0x01);
	disp_line(0);
	LcdWrData(ascii[second[0]/10]);
	LcdWrData(ascii[second[0]%10]);
	LcdWrData(0x27);
	LcdWrData(ascii[second[1]/10]);
	LcdWrData(ascii[second[1]%10]);
	LcdWrData('"');
	LcdWrData(ascii[second[2]/10]);
	LcdWrData(ascii[second[2]%10]);	
}

void time_display(){
	unsigned char i;
	timedisplay[0] = clock.Year/1000;
	timedisplay[1] = clock.Year/100%10;
	timedisplay[2] = clock.Year/10%10;
	timedisplay[3] = clock.Year%10;
	timedisplay[4] = clock.Month/10;
	timedisplay[5] = clock.Month%10;
	timedisplay[6] = clock.Day/10;
	timedisplay[7] = clock.Day%10;
	timedisplay[8] = clock.Hour/10;
	timedisplay[9] = clock.Hour%10;
	timedisplay[10] = clock.Minute/10;
	timedisplay[11] = clock.Minute%10;
	timedisplay[12] = clock.Second/10;
	timedisplay[13] = clock.Second%10;
	for(i = 0; i < 14; i ++){
		if(i == 0)
			disp_line(0);
		if((i == 4)||(i == 6))
			LcdWrData('-');
		if(i == 8)
			disp_line(1);
		if((i == 10)||(i == 12))
			LcdWrData(':');
		if((i == position)&&(flash == 1)){
			if(j >= 25){
				if(j >= 50){
					j = 0;
				}
				LcdWrData(' ');
			}
			else{
				LcdWrData(ascii[timedisplay[i]]);
			}
		}
		else{
			LcdWrData(ascii[timedisplay[i]]);
		}
	}
 }
