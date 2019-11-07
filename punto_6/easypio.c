#include "easypio.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdint.h>

static volatile unsigned int *gpio;

int pioInit(){
  int fd ;

  // Obtain handle to physical memory
  //printf("Opening file /dev/mem...\n");
  if( (fd = open ("/dev/mem", O_RDWR | O_SYNC) ) < 0 ) 
  {
    printf("Unable to open /dev/mem: %s\n", strerror(errno));
    return -1;
  }
  gpio = (volatile unsigned int *)mmap(0, getpagesize(), 
      PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0x3f200000);

  if(gpio < 0)
  {
    printf("Mmap failed: %s\n", strerror(errno));
    return -1;
  }
}
void pinMode(int pin , int inout){
if(INPUT)
switch(pin){
case 1: *(gpio + 2) = (*(gpio + 2) & ~(7 << 18) |(inout<<18) );break;
case 2: *(gpio + 2) = (*(gpio + 2) & ~(7 << 3) |(inout<<3) );break;
case 3: *(gpio + 2) = (*(gpio + 2) & ~(7 << 0) |(inout<<0) );break;
case 4: *(gpio + 1) = (*(gpio + 1) & ~(7 << 18) |(inout<<18) );break;
case 5: *(gpio + 1) = (*(gpio + 1) & ~(7 << 6) |(inout<<6) );break;
case 6: *(gpio + 2) = (*(gpio + 2) & ~(7 << 15) |(inout<<15) );break;
case 7: *(gpio + 2) = (*(gpio + 2) & ~(7 << 12) |(inout<<12) );break;
case 8: *(gpio + 2) = (*(gpio + 2) & ~(7 << 9) |(inout<<9) );break;
}else
switch(pin){
case 9: *(gpio) = (*(gpio) & ~(6 << 15) |(inout<< 15) );break;
case 10: *(gpio) = (*(gpio) & ~(6 << 18) |(inout<<18) );break;
case 11: *(gpio + 1) = (*(gpio + 1) & ~(6 << 9) |(inout<<9) );break;
case 12: *(gpio + 1) = (*(gpio + 1) & ~(6 << 27) |(inout<<27) );break;

}
}
void digitalWrite(int pin , int status){
if(status==1){
switch(pin){
case 1: *(gpio + 7) =  1 << 26  ;break;
case 2: *(gpio + 7) =  1 << 21  ;break;
case 3: *(gpio + 7) =  1 << 20  ;break;
case 4: *(gpio + 7) =  1 << 16  ;break;
case 5: *(gpio + 7) =  1 << 12  ;break;
case 6: *(gpio + 7) =  1 << 25  ;break;
case 7: *(gpio + 7) =  1 << 24  ;break;
case 8: *(gpio + 7) =  1 << 23  ;break;
}
}
else{
switch(pin){
case 1:  *(gpio + 10) =  1 << 26 ;break;
case 2:  *(gpio + 10) =  1 << 21 ;break;
case 3:  *(gpio + 10) =  1 << 20 ;break;
case 4:  *(gpio + 10) =  1 << 16 ;break;
case 5:  *(gpio + 10) =  1 << 12 ;break;
case 6:  *(gpio + 10) =  1 << 25 ;break;
case 7:  *(gpio + 10) =  1 << 24 ;break;
case 8:  *(gpio + 10) =  1 << 23 ;break;
}
}
}
int digitalRead(int pin){
	switch(pin){
	case 9: return  *(gpio+13)&(1<<5)?1:0;
	case 10: return  *(gpio+13)&(1<<6)?1:0;
	case 11: return  *(gpio+13)&(1<<13)?1:0;
	case 12: return  *(gpio+13)&(1<<19)?1:0;
	}
}
void delayMillis(int i){
	for(i=i*1000;i>0;i--);
}


