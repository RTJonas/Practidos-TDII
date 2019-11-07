#include "easypio.h"
int main(){
pioInit();
int luces[8][8]={{1,0,0,0,0,0,0,0},
		 {0,1,0,0,0,0,0,0},
		 {0,0,1,0,0,0,0,0},
		 {0,0,0,1,0,0,0,0},
		 {0,0,0,0,1,0,0,0},
		 {0,0,0,0,0,1,0,0},
		 {0,0,0,0,0,0,1,0},
		 {0,0,0,0,0,0,0,1}};
int i=0,c=0,j=0,d=0,flag=1;
for(i=1;i<9;i++) pinMode( i , OUTPUT);
while(flag){
c=0;
for(j=0;j<8;j++){
for(i=0;i<8;i++)digitalWrite(i+1,luces[i][j]);
if(j>=4){
for(i=0;i<8;i++)digitalWrite(i+1,luces[i][j]|luces[i][j-4+c]);
}
delayMillis(50000);
if(j>=4){
for(i=0;i<8;i++)digitalWrite(i+1,luces[i][j]|luces[i][j-3+c]);
c++;
}
delayMillis(50000);





}
}
}

