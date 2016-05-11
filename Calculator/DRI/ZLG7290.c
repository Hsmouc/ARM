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

void ZLG7290_WriteData(unsigned char address,unsigned char *buf,unsigned char num)
{
    ISendStr(ZLG7290,address,buf,num);
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


unsigned char ZLG7290_SendData(unsigned char SubAdd,unsigned char Data)
{
    I2C_temp[0]=Data;
    if(SubAdd>0x17)
	{
        return 0;
    }
    ZLG7290_WriteData(SubAdd,I2C_temp,1);
	return 1;
}

unsigned char ZLG7290_SendCmd(unsigned char Data1,unsigned char Data2)
{
    I2C_temp[0]=Data1;
    I2C_temp[1]=Data2;
    ZLG7290_WriteData(7,I2C_temp,2);
    delayMS(1);
    return 1;
}  

unsigned char ZLG7290_SendCmd0(unsigned char Data1)
{
    I2C_temp[0]=Data1;

    ZLG7290_WriteData(7,I2C_temp,1);
    delayMS(1);
    return 1;
}  
    

void clear_zlg7290_disp(void)
{
    char i;
    for(i=0;i<8;i++)
    {
        ZLG7290_SendCmd(0x60+i,0x1f);
    }
}

void  zlg7290_disp_keycode(void)
{	
    ZLG7290_SendCmd(0x60,0x0c);
    ZLG7290_SendCmd(0x61,0x00);
    ZLG7290_SendCmd(0x62,0x0d);
    ZLG7290_SendCmd(0x63,0x0e);
	ZLG7290_SendCmd(0x01,0xa6);
	ZLG7290_SendCmd(0x01,0xae);
    ZLG7290_SendCmd(0x66,key_code/10);    
    ZLG7290_SendCmd(0x67,key_code%10);
} 

