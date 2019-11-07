#include<stdio.h>
#include "easypio.h"
#include "kbhit.h"
#define DELAY 5
int main(){
	int i,flag=1;
	pioInit();
	for(i=1;i<9;i++){pinMode(i,OUTPUT);digitalWrite(i,LOW);}
	nonblock(NB_ENABLE);
while(flag){
	delayMillis(DELAY);
	if(kbhit())break;
}
printf("%c %c",8,8);
for(i=1;i<9;i++){digitalWrite(i,LOW);}
return 0;
}
