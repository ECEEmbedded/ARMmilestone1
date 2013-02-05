#include "myADC.h"

void getMsgValue(int *target,vtLCDMsg *lcdBuffer){
	//*(target) = (((int) lcdBuffer->buf[0])<<8)|((int) lcdBuffer->buf[1]);
	*(target) = (int) lcdBuffer->buf[0];
}