#include<reg52.h>
#include<keyscan_basic.h>
#include<hc165.h>
int num_temp = 0;
unsigned char buf[12];
extern unsigned char step;
unsigned char LongToString(int dat){
    signed char i = 0;
    unsigned char len = 0;
   
    if (dat < 0){
        dat = -dat;
        buf[0] = '-';
		i++;
		len++;
    }
   
    do {
        buf[i] = dat % 10;
		i++;
        dat /= 10;
    } while (dat > 0);
    len += i; 
	return len;
}

int number_transfer(int key_transfer) {

	num_temp = num_temp*10 + key_transfer;
	return num_temp;
}

int number_calculate(int num_1, int num_2,unsigned char key) {
	int result;
	switch(key){
		case 0x04: result = num_1 + num_2; break;
		case 0x08: result = num_1 - num_2; break;
		case 0x0C: result = num_1 * num_2; break;
	}
	return result;	
} 

