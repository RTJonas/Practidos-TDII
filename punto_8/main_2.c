
#include<stdio.h>
#include<wiringPi.h>
#include <wiringPiI2C.h>

int main(){
	int serial;
	char dat;
	int fd, result[4],i,flag=1;
	wiringPiSetup();

	if ((serial =serialOpen ("/dev/ttyAMA0", 115200)) < 0)//APERTURA DEL PUERTO
	 {
	 printf ("No se pudo inicializar el puerto");
	 getchar();
	 return 1 ;
	 }
 
        fd=wiringPiI2CSetup(0x48);
        
        while(flag){
        for(i=0;i<4;i++){
        wiringPiI2CWrite (fd,i);
        result[i]=wiringPiI2CRead(fd);
        }//printf("\n");
        serialPrintf(serial,"|%3d|%3d|%3d|%3d|\n",result[0],result[1],result[2],result[3]);
	delay(500);
	}
        printf("\n\n");
        return 0;
}


