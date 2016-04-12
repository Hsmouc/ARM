#include<reg52.h>
#include<clock.h>

int data time[6] = {1970,1,1,0,0,0};
int data second[3] ={0,0,0};
unsigned char timeMs10 = 0;
unsigned char secMs10 = 0;
clockTypeDef clock;
void timeCalc(void){
	timeMs10++;
	if(timeMs10 == 100) {
		timeMs10 = 0;
		time[5]++;
		if(time[5] == 60) {
			time[4]++;
			time[5] = 0;
			if(time[4] == 60) {
				time[3]++;
				time[4] = 0;
				if(time[3] == 24) {
					time[2]++;
					time[3] = 0;
					if(time[1] == 1 || time[1] == 3 || time[1] == 5 || time[1] == 7 || time[1] == 8 || time[1] == 10 || time[1] == 12) {
						if(time[2] == 31) {
							time[1]++;
							time[2] = 0;
							if(time[1] == 12) {
								time[0]++;
							}
						}	
					}
					if(time[1] == 4 || time[1] == 6 || time[1] == 9 || time[1] == 11) {
						if(time[2] == 30) {
							time[1]++;
							time[2] = 0;
						}
					}
					if(time[1] >= 2) {
						if(time[0]%4 == 0) {
							if(time[2] == 29) {
								time[1]++;
								time[2] = 0;
							}
						}
						else
							if(time[2] == 28) {
								time[1]++;
								time[2] = 0;
							}
					}
				}
			}
		} 		
	}
	clock.Year = time[0];
	clock.Month = time[1];
	clock.Day = time[2];
	clock.Hour = time[3];
	clock.Minute = time[4];
	clock.Second = time[5];					
}

void secondCalc(void) {
	secMs10++;
	if(secMs10 == 1) {
		second[2] += 1;
		secMs10 = 0;
		if(second[2] == 99) {
			second[2] = 0;
			second[1]++;
			if(second[1] == 60) {
				second[1] = 0;
				second[0]++;
			}
		}
	}
		
} 