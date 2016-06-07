#include<reg52.h>
#include<keyscan.h>
unsigned char buf[12];
unsigned long num_temp;

unsigned long number_transfer(int key_transfer) {
	num_temp = num_temp * 10 + key_transfer;
	return num_temp;
}

unsigned char password_validate(unsigned long password,unsigned long input) {
	if(password == input) {
		return 1;
	}
	else {
		return 0;
	}
}

unsigned char LongToString(unsigned long dat){
    signed char i = 0;
    unsigned char len = 0;
   
    do {
        buf[i] = dat % 10;
		i++;
        dat /= 10;
    } while (dat > 0);
    len += i; 
	return len;
}

