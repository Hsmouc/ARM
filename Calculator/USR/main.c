#include<reg52.h>
#include<lcd.h>
#include<hc165.h>
#include<display.h>
#include<I2C.h>
void main(){
	hc165_init();
	I2C_Init();
	LcdInit();
	while(1){
		unsigned char key;
		key = hc165_re();
	}
}
