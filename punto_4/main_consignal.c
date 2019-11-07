#include "easypio.h"
#include <signal.h>
int flag=1;
void handler(int );

int main(){
	int i;
	char a;

	pioInit();
	signal(SIGINT, handler);

	for(i=1;i<9;i++){pinMode( i, OUTPUT);digitalWrite( i,LOW);}
	for(i=9;i<13;i++)pinMode( i, INPUT);
	while(flag){
		for(i=1;i<5;i++)digitalWrite( i,digitalRead(i+8));
		delayMillis(100);
	}
	for(i=1;i<9;i++)digitalWrite(i,LOW);
	return 0;
}


void handler(int sig ){
	flag=0;
}
