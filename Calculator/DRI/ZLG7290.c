#include  "i2c.h"
#include  "ZLG7290.h"
#define	EEPROM24C02	0xA0
#define  ZLG7290    0x70     //–æ∆¨µÿ÷∑

#define  SubKey     0x01 
#define  SubCmdBuf  0x07
#define  SubDpRam   0x10

unsigned char key_code=0x4d;
unsigned char key_press=0;

void ZLG7290_ReadData(unsigned char address,unsigned char num)
{
    IRcvStr(ZLG7290,address,I2C_temp,num);
}


void Read_ZLG7290Key(void)
{
    char  usTmp;
    ZLG7290_ReadData(1,1);
    usTmp=I2C_temp[0];
    if(usTmp !=0)
    {
        if(usTmp<0x41)
        {
            key_press=1;
            key_code=usTmp;
        }
    }
}

void delayMS(unsigned int i)
{
	unsigned int j,k;
	for(k=0;k<i;k++)
		for(j=0;j<60;j++);
}

