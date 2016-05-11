#include  "I2C.H"
#include <REG52.H>
#include <intrins.h>

#define  NOP()   _nop_()   
#define  _Nop()  _nop_()  

sbit     SCL=P1^6;    
sbit     SDA=P1^7;    

bit ack;                 

unsigned char I2C_temp[8]={"01234567"};                

void Start_I2c()
{
  	SDA=1;         
  	_Nop();
  	SCL=1;
  	I2C_delay(10);   
  	SDA=0;        
  	I2C_delay(10);   
  	SCL=0;       
  	I2C_delay(10);   
}

void Stop_I2c()
{
  	SDA=0;      
  	_Nop();      
  	SCL=1;      
  	I2C_delay(10);   
  	SDA=1;      
  	I2C_delay(10);   
}

void  SendByte(unsigned char  c)
{
 	unsigned char  BitCnt;
 
 	for(BitCnt=0;BitCnt<8;BitCnt++) 
    {
     	if((c<<BitCnt)&0x80)SDA=1;   
       		else  SDA=0;                
     	_Nop();
     	SCL=1;
  		I2C_delay(10);   
     	SCL=0; 
  		I2C_delay(10);   
    }
  	I2C_delay(10);   
    SDA=1;               
  	I2C_delay(10);   
    SCL=1;
  	I2C_delay(10);   
    if(SDA==1)ack=0;     
       else ack=1;       
    SCL=0;
  	I2C_delay(10);   
}
   
unsigned char   RcvByte()
{
  	unsigned char  retc;
  	unsigned char  BitCnt;
  
  	retc=0; 
  	SDA=1;                     
  	for(BitCnt=0;BitCnt<8;BitCnt++)
    {
  		I2C_delay(10);   
        SCL=0;              
	  	I2C_delay(10);   
        SCL=1;                  
  		I2C_delay(10);   
        retc=retc<<1;
        if(SDA==1)retc=retc+1; 
  		I2C_delay(10);   
    }
  	SCL=0;    
  	I2C_delay(10);   
  	return(retc);
}

void Ack_I2c(bit a)
{
  	if(a==0)SDA=0;        
  		else SDA=1;
  	I2C_delay(10);   
  	SCL=1;
  	I2C_delay(10);   
  	SCL=0;                
  	I2C_delay(10);   
}

bit ISendStr(unsigned char  sla,unsigned char  suba,unsigned char  *s,unsigned char  no)
{
   	unsigned char i;

   	Start_I2c();           
   	SendByte(sla);          
   	if(ack==0)return(0);
   	SendByte(suba);          
   	if(ack==0)return(0);

   	for(i=0;i<no;i++)
   	{   
     	SendByte(*s);        
     	if(ack==0)return(0);
     	s++;
   	} 
   	Stop_I2c();                

   	return(1);
}

bit IRcvStr(unsigned char  sla,unsigned char  suba,unsigned char  *s,unsigned char  no)
{
   	unsigned char i;

   	Start_I2c();                
   	SendByte(sla);               
   	if(ack==0)return(0);
   	SendByte(suba);            
   	if(ack==0)return(0);

   	Start_I2c();                
   	SendByte(sla+1);
   	if(ack==0)return(0);
   	for(i=0;i<no-1;i++)
   	{   
     	*s=RcvByte();             
      	Ack_I2c(0);                 
     	s++;
   	} 
   	*s=RcvByte();
   	Ack_I2c(1);                   
   	Stop_I2c();                    
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


