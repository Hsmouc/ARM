#include<reg52.h>
#include<keyscan_basic.h>
#include<hc165.h>

unsigned char step = 0;
unsigned char LongToString(unsigned char *str, signed int dat){
    signed char i = 0;
    unsigned char len = 0;
    unsigned char buf[12];
   
    if (dat < 0){
        dat = -dat;
        *str++ = '-';
		len++;
    }
   
    do {
        buf[i++] = dat % 10;
        dat /= 10;
    } while (dat > 0);
    len += i;
    while (i-- > 0){
        *str++ = buf[i] + '0';
    }
    *str = '\0';
	return len;
}

int num_transfer(unsigned char key) {
	int num_transfer = 0;
	num_transfer = num_transfer*10 + keyscan_tranfer(key);
	return num_transfer;
}

int num_calculate(unsigned char key) {
	int data_1,data_2,result;
	if(step == 0)
		data_1 = num_transfer(key);
	else
		data_2 = num_transfer(key);
	switch(key) {
		case 0x80: result = data_1 + data_2; step = 0; return result;
	}	
} 

