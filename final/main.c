#include <stdio.h>
#include <termios.h>
#include <string.h>
#include <stdlib.h>
#include "kbhit.h"
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define PAS "5554555"
#define FD_STDIN 0

#define LED8 4
#define LED7 5
#define LED6 6
#define LED5 26
#define LED4 27
#define LED3 28
#define LED2 29
#define LED1 25

char acceso();
void menu(char*);
void choque(int *,char *);
int interrupt(char ,int *,int);
void grafica(char, int *);
void autofantastic(int *,char *);
void carrera(int *, char *);
void baliza(int*,char*);
void anillo(int *,char *);
void seteo(int *);
int main(){
	int i;
	char vector[8]={LED1,LED2,LED3,LED4,LED5,LED6,LED7,LED8};
        wiringPiSetup () ;
        for(i=0;i<8;i++) pinMode(vector[i],OUTPUT);
	if(1){
	nonblock(NB_ENABLE);
	menu(vector);
	}else printf("Acceso denegado\n");
}
char acceso(){
	struct termios term;
        char pass[10]={'\0'};
        char a;
        int i=0,cont=0;
        do{
        i=0;
        tcgetattr(FD_STDIN, &term);
        term.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(FD_STDIN, TCSANOW, &term);
        printf("Ingrese Contraseña: ");
        while(i<7){
        a=getchar();
        if(('0'<=a) && (a<='9')){
        pass[i]=a;
        printf("*");i++;
        }
        else if(a==127&&i>0){
        printf("%c %c",8,8);
        i--;
        }
        }
        tcgetattr(FD_STDIN, &term);
        term.c_lflag |= (ICANON | ECHO);
        tcsetattr(FD_STDIN, TCSANOW, &term);
	if (strcmp(pass,PAS)== 0){
        return 1;
        }
        else printf("\n Contraseña incorrecta.\n");
        cont++;
        }while(cont<3);
	return 0;
}
void menu(char *vector){
	int velocidad=100,flag=1;
	grafica(0,&velocidad);
	do{
	if(kbhit()){
		printf("%c %c",8,8);
		switch(getchar()){
			case '1':autofantastic(&velocidad,vector);break;
			case '2':choque(&velocidad,vector);break;
                        case '3':break;
			case '4':carrera(&velocidad,vector);break;
			case '5':anillo(&velocidad,vector);break;
			case '6':break;
			case '7':break;
			case '8':baliza(&velocidad,vector);break;
			case 'l':break;
			case 'r':break;
			case 's':seteo(&velocidad);break;
			case 'x':flag=0;
		}
	}
	}while(flag);
}
int interrupt(char op,int *velocidad,int flag){
	if(kbhit()){
		switch(getchar()){
			case 'c':return 0;
			case '+':
			if(*velocidad>10)*velocidad=*velocidad-10;
				break;
			case '-':
			if(*velocidad<250)*velocidad=*velocidad+10;
				break;
			default:return 1;
		}
	grafica(op,velocidad);
	}
	if(op==12)grafica(op,velocidad);
	if(flag==0)return 0;
	else return 1;
}
void choque(int *velocidad, char *vector){
	int flag=1,i=0;
	char op=2;
	grafica(op,velocidad);
	while(flag){
	        digitalWrite (vector[i], HIGH) ;  
        	digitalWrite (vector[7-i],HIGH);delay(*velocidad);
		flag=interrupt(1,velocidad,flag);
        	digitalWrite (vector[i],LOW);
        	digitalWrite (vector[7-i],LOW);delay(*velocidad);
        	i++;
        	if(i>7)i=0;
		flag=interrupt(op,velocidad,flag);
        }
	for(i=0;i<8;i++)digitalWrite (vector[i],LOW);
	grafica(0,velocidad);
}
void autofantastic(int *velocidad,char *vector){
	int flag=1,i=0;
	char op=1;
	grafica(op,velocidad);
	while(flag){
	for(i=0;flag==1&&i<8;i++){
        	digitalWrite(vector[i],HIGH);
        	delay(*velocidad);
		flag=interrupt(op,velocidad,flag);
        	if(i>0)digitalWrite(vector[i-1],LOW);
        	delay(*velocidad);
        	flag=interrupt(op,velocidad,flag);
        }
	for(i=7;flag==1&&i>=0;i--){
        	flag=interrupt(op,velocidad,flag);
        	digitalWrite(vector[i],HIGH);
        	delay(*velocidad);
		flag=interrupt(op,velocidad,flag);
        	if(i<8)digitalWrite(vector[i+1],LOW);
        	delay(*velocidad);
        }
        flag=interrupt(op,velocidad,flag);
	}
	for(i=0;i<8;i++)digitalWrite(vector[i],LOW);
	grafica(0,velocidad);
}
void carrera(int *velocidad, char *vector){
	char luces[8][8]={{1,0,0,0,0,0,0,0},
                 {0,1,0,0,0,0,0,0},
                 {0,0,1,0,0,0,0,0},
                 {0,0,0,1,0,0,0,0},
                 {0,0,0,0,1,0,0,0},
                 {0,0,0,0,0,1,0,0},
                 {0,0,0,0,0,0,1,0},
                 {0,0,0,0,0,0,0,1}};
	int i=0,c=0,j=0,d=0,flag=1;
	char op=4;
	grafica(op,velocidad);
while(flag){
c=0;
for(j=0;flag==1&&j<8;j++){
        for(i=0;flag==1&&i<8;i++){
                digitalWrite(vector[i],luces[i][j]);
                flag=interrupt(op,velocidad,flag);

        }
        if(j>=4){
                for(i=0;flag==1&&i<8;i++){
                        digitalWrite(vector[i],luces[i][j]|luces[i][j-4+c]);
                        flag=interrupt(op,velocidad,flag);
                }

        }
        flag=interrupt(op,velocidad,flag);
	delay(*velocidad);
	if(j>=4){
        	for(i=0;flag==1&&i<8;i++){
                	digitalWrite(vector[i],luces[i][j]|luces[i][j-3+c]);
                	flag=interrupt(op,velocidad,flag);
                }
                c++;
        }
	flag=interrupt(op,velocidad,flag);
	delay(*velocidad);
	}
	flag=interrupt(op,velocidad,flag);
	}
	for(i=1;i<9;i++)digitalWrite(vector[i],LOW);
	grafica(0,velocidad);

}
void anillo(int *velocidad,char *vector){
	int flag=1,i=0,op=5;
        grafica(op,velocidad);
        while(flag){
        for(i=0;flag==1&&i<8;i++){
		digitalWrite(vector[i],HIGH);
                delay(*velocidad);
		if(i==0)digitalWrite(vector[7],LOW);
                if(i>0)digitalWrite(vector[i-1],LOW);
		flag=interrupt(op,velocidad,flag);
                delay(*velocidad);
                flag=interrupt(op,velocidad,flag);
        	}
	}
	for(i=1;i<9;i++)digitalWrite(vector[i],LOW);
	grafica(0,velocidad);

}

void baliza(int *velocidad,char *vector){
	int i,flag=1,op=8;
	grafica(op,velocidad);
	while(flag){
	flag=interrupt(op,velocidad,flag);
	for(i=0;flag==1&&i<8;i++)digitalWrite(vector[i],HIGH);
	delay(*velocidad);
	flag=interrupt(op,velocidad,flag);
	for(i=0;flag==1&&i<8;i++)digitalWrite(vector[i],LOW);
	delay(*velocidad);
	}
	for(i=0;i<8;i++)digitalWrite(vector[i],LOW);
	grafica(0,velocidad);
}
void seteo(int *velocidad){
	int fd, result,flag=1;
	char op =12;
	printf("datos del sensor:\n"); 
	fd=wiringPiI2CSetup(0x48);
	while(flag){
	flag=interrupt(op,velocidad,flag);
	wiringPiI2CWrite(fd,0);
        result=wiringPiI2CRead(fd);
	if(result)*velocidad=(result*250)/255;
	else *velocidad=result;
	delay(100);
	}
}

void grafica(char op,int *velocidad){
	system("clear");//Al final va reset
        printf("%20c#####################################\n",35);
        printf("%20c Trabajo final Tecnicas Digitales 2 #\n",35);
        printf("%20c#####################################\n",35);
	printf("\n\n%10c Secuencias de luces:\n",62);
        if(op==1)printf("%13cx]",91);else printf("%13c ]",91);
	printf("(1) El auto fantastico.\n");
        if(op==2)printf("%13cx]",91);else printf("%13c ]",91);
	printf("(2) El choque.\n");
        if(op==3)printf("%13cx]",91);else printf("%13c ]",91);
	printf("(3) La apilada.\n");
        if(op==4)printf("%13cx]",91);else printf("%13c ]",91);
	printf("(4) La carrera.\n");
	if(op==5)printf("%13cx]",91);else printf("%13c ]",91);
	printf("(5) Anillo.\n");
	if(op==6)printf("%13cx]",91);else printf("%13c ]",91);
	printf("(6) Vumetro vertical.\n");
	if(op==7)printf("%13cx]",91);else printf("%13c ]",91);
	printf("(7) Vumetro horizontal.\n",91);
	if(op==8)printf("%13cx]",91);else printf("%13c ]",91);
	printf("(8) Baliza.\n");
	printf("\n %20celocidad: %d\n\n",86,((250-(*velocidad))*100)/250);
        printf("%10c Metodos de operacion:\n",62);
	if(op<9||op==12)printf("%13cx]",91);else printf("%13c ]",91);
	printf("(l) Local.\n");
	if(op==9)printf("%13cx]",91);else printf("%13c ]",91);
	printf("(r) Remoto-Cliente.\n");
	if(op==10)printf("%13cx]",91);else printf("%13c ]",91);
	printf("(t) Remoto-Servidor.\n\n");
	printf("%10c Opciones\n",62);
        printf("%13cc) Salir de secuencias.\n",40);
        printf("%13cs) Setear velocidades iniciales.\n",40);
        printf("%13cx) Salir del programa.\n",40);
	if(op!=12)printf(": ");
}
