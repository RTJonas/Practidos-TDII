#include <stdio.h>
#include <termios.h>
#include <string.h>
#include <stdlib.h>
#include "kbhit.h"
#include <wiringPi.h>
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
char interrupt(char ,int *);
void grafica(char, int *);
void autofantastic(int *,char *);
int main(){
	int i;
	char vector[8]={25,29,28,27,26,6,5,4};
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
	if(kbhit())
		switch(getchar()){
			case '1':choque(&velocidad,vector);printf("%c:",13);break;
			case '2':autofantastic(&velocidad,vector);break;
			case 'x':flag=0;
		}
	}while(flag);
}
char interrupt(char op,int *velocidad){
	char llamado=getchar();
	printf("%c %c",8,8);
	if(llamado=='c'){
	grafica(0,velocidad);
	return 0;
	}
	else{
	switch(llamado){
	case '+':if(*velocidad>10)*velocidad=*velocidad-10;break;
	case '-': if(*velocidad<250)*velocidad=*velocidad+1;break;
	}
	grafica(op,velocidad);
	}
	return 1;
}
void choque(int *velocidad, char *vector){
	int flag=1,i=0;
	grafica(1,velocidad);
	while(flag){
	        digitalWrite (vector[i], HIGH) ;  
        	digitalWrite (vector[7-i],HIGH);delay(*velocidad);
		if(kbhit())flag=interrupt(1,velocidad);
        	digitalWrite (vector[i],LOW);
        	digitalWrite (vector[7-i],LOW);delay(*velocidad);
        	i++;
        	if(i>7)i=0;
		if(kbhit())flag=interrupt(1,velocidad);
        }
	for(i=0;i<8;i++)digitalWrite (vector[i],LOW);
	
}
void autofantastic(int *velocidad,char *vector){
	int flag=1,i=0,op=2;
	grafica(op,velocidad);
	while(flag){
	for(i=0;flag==1&&i<8;i++){
        	digitalWrite(vector[i],HIGH);
        	delay(*velocidad);
        	if(i>0)digitalWrite(vector[i-1],LOW);
        	delay(*velocidad);
        	if(kbhit())flag=interrupt(op,velocidad);
        }
	for(i=7;flag==1&&i>=0;i--){
        	if(kbhit())flag=interrupt(op,velocidad);
        	digitalWrite(vector[i],HIGH);
        	delay(*velocidad);
        	if(i<8)digitalWrite(vector[i+1],LOW);
        	delay(*velocidad);
        }
        if(kbhit())flag=interrupt(op,velocidad);
	}
	for(i=0;i<8;i++)digitalWrite(vector[i],LOW);

}

void grafica(char op,int *velocidad){
	system("clear");//Al final va reset
        printf("%20c#####################################\n",35);
        printf("%20c Trabajo final Tecnicas Digitales 2 #\n",35);
        printf("%20c#####################################\n",35);

	printf("\n\n%10c Secuencias de luces:\n",62);
        if(op==1)printf("%13cx](1) El auto fantastico.\n",91);
	else printf("%13c ](1) El auto fantastico.\n",91);
        if(op==2)printf("%13cx](2) El choque.\n",91);
	else printf("%13c ](2) El choque.\n",91);
        if(op==3)printf("%13cx](3) La apilada.\n",91);
	else printf("%13c ](3) La apilada.\n",91);
        if(op==4)printf("%13cx](4) La carrera.\n",91);
        else printf("%13c ](4) La carrera.\n",91);
	if(op==5)printf("%13cx](5) Anillo.\n",91);
        else printf("%13c ](5) Anillo.\n",91);
	if(op==6)printf("%13cx](6) Vumetro vertical.\n",91);
        else printf("%13c ](6) Vumetro vertical.\n",91);
	if(op==7)printf("%13cx](7) Vumetro horizontal.\n",91);
        else printf("%13c ](7) Vumetro horizontal.\n",91);
	if(op==8)printf("%13cx](8) Baliza.\n",91);
        else printf("%13c ](8) Baliza.\n",91);

	printf("\n %20celocidad: %d\n\n",86,((250-(*velocidad))*100)/250);
        printf("%10c Metodos de operacion:\n",62);
	if(op==9)printf("%13cx](l) Local.\n",91);
        else printf("%13c ](l) Local.\n",91);
	if(op==10)printf("%13cx](r) Remoto.\n\n",91);
        else printf("%13c ](r) Remoto.\n\n",91);
	printf("%10c Opciones\n",62);
        printf("%13cc) Salir de secuencias.\n",40);
        printf("%13cs) Setear velocidades iniciales.\n",40);
        printf("%13cx) Salir del programa.\n",40);
	printf(": ");
}
