#ifndef _LCD_H
#define _LCD_H

void senddata(unsigned char);
void Delay1ms(unsigned int);
void LcdWrCmd(unsigned char);
void LcdWrData(unsigned char);
void disp_line(unsigned char);
void LcdInit(void);

#endif
