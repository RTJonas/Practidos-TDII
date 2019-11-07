#include "kbhit.h"
#include<stdio.h>
#include<wiringPi.h>
#include <wiringPiI2C.h>
int main(){
	int fd, result[4],i,flag;
	nonblock(NB_ENABLE);
	printf("datos del sensor:");	
	fd=wiringPiI2CSetup(0x48);
	while(flag){
	for(i=0;i<4;i++){
	wiringPiI2CWrite (fd,i);
	result[i]=wiringPiI2CRead(fd);
	if(kbhit()){break;flag=0;}
	}//printf("\n");
	printf("|%3d|%3d|%3d|%3d|",result[0],result[1],result[2],result[3]);
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8);
	if(kbhit()){break;flag=0;}
	}
	printf("\n\n");
	return 0;
}
