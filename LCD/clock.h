#ifndef _CLOCK_H_
#define _CLOCK_H_

typedef struct{
	int Year;
	int Month;
	int Day;
	int Hour;
	int Minute;
	int Second;
}clockTypeDef; 	

void timeCalc(void);
void secondCalc(void);	

#endif