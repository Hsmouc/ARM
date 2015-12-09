#include<reg51.h>
#include<intrins.h>

#define GPIO_LED P2

void Delay10ms(unsigned int);
void main(void)
{
	unsigned char n;
	GPIO_LED=0xfe;//1111_1110->1111_1101
	while(1)
	{
		for(n=0;n<7;n++)
		{
			GPIO_LED=_crol_(GPIO_LED,1);
			Delay10ms(50);
		}
		for(n=0;n<7;n++)
		{
			GPIO_LED=_cror_(GPIO_LED,1);
			Delay10ms(50);
		}	
	}	
}
void Delay10ms(unsigned int c)
{
    unsigned char a,b;
    for(;c>0;c--)
        for(b=38;b>0;b--)
            for(a=130;a>0;a--);
}