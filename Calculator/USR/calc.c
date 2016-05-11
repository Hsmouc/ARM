#include<reg52.h>
#include<keyscan_basic.h>
#include<hc165.h>
int num_temp = 0;
unsigned char buf[12];
unsigned char step = 0;
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

int num_transfer(unsigned char key) {
	num_temp = num_temp*10 + keyscan_tranfer(key);
	return num_temp;
}

int num_calculate(unsigned char key) {
	int data_1,data_2,result;
	if(step == 0)
		data_1 = num_transfer(key);
	else
		data_2 = num_transfer(key);
	switch(key) {
		case 0x80: result = data_1 + data_2; step = 0; return result;
		default: return 0;
	}	
} 

