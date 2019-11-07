#include<stdio.h>
#include "easypio.h"
#include<stdlib.h>
#include "kbhit.h"
#include<string.h>
int main(){
	int i;
	char in;
	pioInit();
	for(i=1;i<9;i++){pinMode( i, OUTPUT);digitalWrite( i,LOW);}
	for(i=9;i<13;i++)pinMode( i, INPUT);
	printf("Presionar x para salir: ");
	nonblock(NB_ENABLE);
	while(1){
		for(i=1;i<5;i++)printf("|%d|",digitalRead(i+8));
		printf("\n");
		for(i=1;i<5;i++)digitalWrite(i,digitalRead(i+8));
		delayMillis(100);
		if(kbhit()){
			if(getchar()=='x')break;
			else printf("%c %c",8,8);
		}
	}
	for(i=1;i<9;i++)digitalWrite(i,LOW);
	printf("%c %c\n",8,8);
	return 0;
}
