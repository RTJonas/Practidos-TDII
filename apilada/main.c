#include<stdio.h>
#include<wiringPi.h>
#include<stdlib.h>
#include "kbhit.h"
#include<string.h>
#include<stdbool.h>
int main(){
	int i,j,k=0;
	bool tarro[8][8]={
        {0,0,0,0,0,0,0,0},
	{1,0,0,0,0,0,0,0},
	{0,1,0,0,0,0,0,0},
	{0,0,1,0,0,0,0,0},
	{0,0,0,1,0,0,0,0},
	{0,0,0,0,1,0,0,0},
	{0,0,0,0,0,1,0,0},
	{0,0,0,0,0,0,0,1},
	};
	#define LED8 4
	#define LED7 5
	#define LED6 6
	#define LED5 26
	#define LED4 27
	#define LED3 28
	#define LED2 29
	#define LED1 25
	char vector[8]={LED1,LED2,LED3,LED4,LED5,LED6,LED7,LED8};
	wiringPiSetup();
	for(i=0;i<8;i++){pinMode( vector[i], OUTPUT);digitalWrite(vector[i],0);}
	nonblock(NB_ENABLE);
	while(1){
		for(j=0;j<8-k;j++){
			for(i=0;i<8-k;i++){
				digitalWrite(vector[i],tarro[i][j]);
				delay(200);
			}
			if(j+k==7)k++;
			if(k==7)k=0;
		}
		if(kbhit()){
			if(getchar()=='x')break;
			else printf("%c %c",8,8);
		}
	}
	for(i=0;i<8;i++)digitalWrite(vector[i],0);
	printf("%c %c\n",8,8);
	return 0;
}
