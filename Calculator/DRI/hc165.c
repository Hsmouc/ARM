#include<reg52.h>
sbit hc165_sdo=P2^5;
sbit hc165_sclk=P2^6;
sbit hc165_pl=P2^7;

void hc165_init(){
	hc165_sdo=1;
	hc165_sclk=0;
	hc165_pl=1;
}

unsigned char hc165_re(void){
	unsigned i,x=0;
	hc165_pl=0;
	x=x+0;
	hc165_pl=1;
	if( hc165_sdo == 1 )
		x = x + 1;
	for( i = 0;i < 7;i ++){
		hc165_sclk=1;
		x = x << 1;
		hc165_sclk=0;
		if( hc165_sdo == 1 )
			x = x + 1;
	}
	return x;
}
