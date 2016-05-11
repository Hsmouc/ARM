#include  "I2C.H"
#include <REG52.H>
#include <intrins.h>

#define  NOP()   _nop_()   /* 定义空指令 */
#define  _Nop()  _nop_()   /*定义空指令*/

sbit     SCL=P1^6;     //I2C  时钟 
sbit     SDA=P1^7;     //I2C  数据 

bit ack;                 /*应答标志位*/

unsigned char I2C_temp[8]={"01234567"};                  //时间交换区,全局变量声明/

void Start_I2c()
{
  	SDA=1;         /*发送起始条件的数据信号*/
  	_Nop();
  	SCL=1;
  	I2C_delay(10);   
  	SDA=0;         /*发送起始信号*/
  	I2C_delay(10);   
  	SCL=0;       /*钳住I2C总线，准备发送或接收数据 */
  	I2C_delay(10);   
}

void Stop_I2c()
{
  	SDA=0;      /*发送结束条件的数据信号*/
  	_Nop();       /*发送结束条件的时钟信号*/
  	SCL=1;      /*结束条件建立时间大于4μs*/
  	I2C_delay(10);   
  	SDA=1;      /*发送I2C总线结束信号*/
  	I2C_delay(10);   
}

void  SendByte(unsigned char  c)
{
 	unsigned char  BitCnt;
 
 	for(BitCnt=0;BitCnt<8;BitCnt++)  /*要传送的数据长度为8位*/
    {
     	if((c<<BitCnt)&0x80)SDA=1;   /*判断发送位*/
       		else  SDA=0;                
     	_Nop();
     	SCL=1;               /*置时钟线为高，通知被控器开始接收数据位*/
  		I2C_delay(10);   
     	SCL=0; 
  		I2C_delay(10);   
    }
  	I2C_delay(10);   
    SDA=1;                /*8位发送完后释放数据线，准备接收应答位*/
  	I2C_delay(10);   
    SCL=1;
  	I2C_delay(10);   
    if(SDA==1)ack=0;     
       else ack=1;        /*判断是否接收到应答信号*/
    SCL=0;
  	I2C_delay(10);   
}
   
unsigned char   RcvByte()
{
  	unsigned char  retc;
  	unsigned char  BitCnt;
  
  	retc=0; 
  	SDA=1;                       /*置数据线为输入方式*/
  	for(BitCnt=0;BitCnt<8;BitCnt++)
    {
  		I2C_delay(10);   
        SCL=0;                  /*置时钟线为低，准备接收数据位*/
	  	I2C_delay(10);   
        SCL=1;                  /*置时钟线为高使数据线上数据有效*/
  		I2C_delay(10);   
        retc=retc<<1;
        if(SDA==1)retc=retc+1;  /*读数据位,接收的数据位放入retc中 */
  		I2C_delay(10);   
    }
  	SCL=0;    
  	I2C_delay(10);   
  	return(retc);
}

void Ack_I2c(bit a)
{
  	if(a==0)SDA=0;              /*在此发出应答或非应答信号 */
  		else SDA=1;
  	I2C_delay(10);   
  	SCL=1;
  	I2C_delay(10);   
  	SCL=0;                     /*清时钟线，钳住I2C总线以便继续接收*/
  	I2C_delay(10);   
}

bit ISendStr(unsigned char  sla,unsigned char  suba,unsigned char  *s,unsigned char  no)
{
   	unsigned char i;

   	Start_I2c();               /*启动总线*/
   	SendByte(sla);             /*发送器件地址*/
   	if(ack==0)return(0);
   	SendByte(suba);            /*发送器件子地址*/
   	if(ack==0)return(0);

   	for(i=0;i<no;i++)
   	{   
     	SendByte(*s);            /*发送数据*/
     	if(ack==0)return(0);
     	s++;
   	} 
   	Stop_I2c();                /*结束总线*/ 

   	return(1);
}

bit IRcvStr(unsigned char  sla,unsigned char  suba,unsigned char  *s,unsigned char  no)
{
   	unsigned char i;

   	Start_I2c();                  /*启动总线*/
   	SendByte(sla);                /*发送器件地址*/
   	if(ack==0)return(0);
   	SendByte(suba);               /*发送器件子地址*/
   	if(ack==0)return(0);

   	Start_I2c();                 /*重新启动总线*/
   	SendByte(sla+1);
   	if(ack==0)return(0);
   	for(i=0;i<no-1;i++)
   	{   
     	*s=RcvByte();               /*发送数据*/
      	Ack_I2c(0);                /*发送就答位*/  
     	s++;
   	} 
   	*s=RcvByte();
   	Ack_I2c(1);                   /*发送非应位*/
   	Stop_I2c();                   /*结束总线*/ 
   	return(1);
}

void  I2C_Init(void)
{
    SCL=1;
    SDA=1;
}

void I2C_delay(unsigned char dly)
{
	while(dly--);
}


