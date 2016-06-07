#include<reg52.h>
#include<keyscan.h>

int key_transfer(unsigned char key) {
   int keyscan_transfer = 0;
	switch(key) {
		case 0x01:keyscan_transfer = 1; break; 
		case 0x02:keyscan_transfer = 2; break; 
		case 0x03:keyscan_transfer = 3; break;
		case 0x04:keyscan_transfer = 0; break;
		case 0x05:keyscan_transfer = 4;	break;
		case 0x06:keyscan_transfer = 5; break;
		case 0x07:keyscan_transfer = 6; break;
		case 0x08:keyscan_transfer = 0; break;
		case 0x09:keyscan_transfer = 7; break;
		case 0x0A:keyscan_transfer = 8; break; 
		case 0x0B:keyscan_transfer = 9; break;
		case 0x0C:keyscan_transfer = 0; break;
		case 0x0D:keyscan_transfer = 0; break;
		case 0x0E:keyscan_transfer = 0; break;
		case 0x0F:keyscan_transfer = 0; break;
		case 0x10:keyscan_transfer = 0;break; 
	}
	return keyscan_transfer;
}
