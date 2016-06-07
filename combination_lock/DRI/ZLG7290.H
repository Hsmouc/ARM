#ifndef  _ZLG7290_H_
#define  _ZLG7290_H_

extern unsigned char key_code;
extern unsigned char key_press;

extern int ReadData_7290(int address); /*µ¥×Ö½Ú*/

extern unsigned char ZLG7290_SendCmd(unsigned char,unsigned char);

extern void  Read_ZLG7290Key(void);

extern void delayMS(unsigned int i);

extern void ZLG7290_SendBuf(unsigned char * disp_buf,unsigned char num);

extern void zlg7290_test(void);


#endif  // _ZLG7290_H_