#include <stdio.h>
#include <termios.h>
#include <string.h>
#include <stdlib.h>
#include "kbhit.h"
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <wiringSerial.h>
#include <stdbool.h>
#include<time.h>

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
void choque(int *,char *,char,int,char);
int interrupt(char ,int *,int,char,int);
void grafica(char, int *);
void autofantastic(int *,char *,char,int,char);
void carrera(int *, char *,char,int,char);
void baliza(int*,char*,char,int,char);
void anillo(int *,char *,char,int,char);
void apilada(int *, char *,char,int,char);
void vumetro_vertical(int *,char *,char,int,char);
void vumetro_hor(int *,char *,char,int,char);
void seteo(int *,char,int);
int maestro(int*,char);
int esclavo(int*,char *);
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
	int velocidad=100,flag=1,fd=0;
	char modo=0;
	grafica(0,&velocidad);
	do{
	if(kbhit()){
		printf("%c %c",8,8);
		switch(getchar()){
			case '1':autofantastic(&velocidad,vector,modo,fd,1);break;
			case '2':choque(&velocidad,vector,modo,fd,2);break;
                        case '3':apilada(&velocidad,vector,modo,fd,3);break;
			case '4':carrera(&velocidad,vector,modo,fd,4);break;
			case '5':anillo(&velocidad,vector,modo,fd,5);break;
			case '6':vumetro_vertical(&velocidad,vector,modo,fd,6);break;
			case '7':vumetro_hor(&velocidad,vector,modo,fd,7);break;
			case '8':baliza(&velocidad,vector,modo,fd,8);break;
			case 'e':esclavo(&velocidad,vector);break;
			case 'm':maestro(&velocidad,modo);break;
			case 's':seteo(&velocidad,modo,fd);break;
			case 'x':flag=0;
		}
		grafica(0,&velocidad);
	}
	}while(flag);
}
int interrupt(char op,int *velocidad,int flag,char modo,int fd){
	if(modo==1){
		if(kbhit())if(getchar()=='c')return 0;
		if(serialDataAvail(fd)){
			switch(serialGetchar(fd)){
                        	case 't':if(op!=10)return 0;break;
                        	case '+':
                        	if(*velocidad>10)
				*velocidad=*velocidad-10;
                                grafica(op,velocidad);
				break;
                        	case '-':
                        	if(*velocidad<250)
				*velocidad=*velocidad+10;
				grafica(op,velocidad);
                                break;
				case 'k':if(op==10)return 0;
                        default:return 1;
                	}
		}
	}
	if(kbhit()&&modo==0){
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
void choque(int *velocidad, char *vector,char modo,int fd,char op){
	int flag=1,i=0;
	grafica(op,velocidad);
	while(flag){
	        digitalWrite (vector[i], HIGH) ;
        	digitalWrite (vector[7-i],HIGH);delay(*velocidad);
		flag=interrupt(op,velocidad,flag,modo,fd);
        	digitalWrite (vector[i],LOW);
        	digitalWrite (vector[7-i],LOW);delay(*velocidad);
        	i++;
        	if(i>7)i=0;
		flag=interrupt(op,velocidad,flag,modo,fd);
        }
	for(i=0;i<8;i++)digitalWrite (vector[i],LOW);
}
void autofantastic(int *velocidad,char *vector,char modo,int fd,char op){
	int flag=1,i=0;
	grafica(op,velocidad);
	while(flag){
	for(i=0;flag==1&&i<8;i++){
        	digitalWrite(vector[i],HIGH);
        	delay(*velocidad);
		flag=interrupt(op,velocidad,flag,modo,fd);
        	if(i>0)digitalWrite(vector[i-1],LOW);
        	delay(*velocidad);
        	flag=interrupt(op,velocidad,flag,modo,fd);
        }
	for(i=7;flag==1&&i>=0;i--){
        	flag=interrupt(op,velocidad,flag,modo,fd);
        	digitalWrite(vector[i],HIGH);
        	delay(*velocidad);
		flag=interrupt(op,velocidad,flag,modo,fd);
        	if(i<8)digitalWrite(vector[i+1],LOW);
        	delay(*velocidad);
        }
        flag=interrupt(op,velocidad,flag,modo,fd);
	}
	for(i=0;i<8;i++)digitalWrite(vector[i],LOW);
}
void carrera(int *velocidad, char *vector,char modo,int fd,char op){
	char luces[8][8]={{1,0,0,0,0,0,0,0},
                 {0,1,0,0,0,0,0,0},
                 {0,0,1,0,0,0,0,0},
                 {0,0,0,1,0,0,0,0},
                 {0,0,0,0,1,0,0,0},
                 {0,0,0,0,0,1,0,0},
                 {0,0,0,0,0,0,1,0},
                 {0,0,0,0,0,0,0,1}};
	int i=0,c=0,j=0,d=0,flag=1;
	grafica(op,velocidad);
while(flag){
c=0;
for(j=0;flag==1&&j<8;j++){
        for(i=0;flag==1&&i<8;i++){
                digitalWrite(vector[i],luces[i][j]);
                flag=interrupt(op,velocidad,flag,modo,fd);

        }
        if(j>=4){
                for(i=0;flag==1&&i<8;i++){
                        digitalWrite(vector[i],luces[i][j]|luces[i][j-4+c]);
                        flag=interrupt(op,velocidad,flag,modo,fd);
                }

        }
        flag=interrupt(op,velocidad,flag,modo,fd);
	delay(*velocidad);
	if(j>=4){
        	for(i=0;flag==1&&i<8;i++){
                	digitalWrite(vector[i],luces[i][j]|luces[i][j-3+c]);
                	flag=interrupt(op,velocidad,flag,modo,fd);
                }
                c++;
        }
	flag=interrupt(op,velocidad,flag,modo,fd);
	delay(*velocidad);
	}
	flag=interrupt(op,velocidad,flag,modo,fd);
	}
	for(i=1;i<9;i++)digitalWrite(vector[i],LOW);

}
void anillo(int *velocidad,char *vector,char modo,int fd,char op){
	int flag=1,i=0;
        grafica(op,velocidad);
        while(flag){
        for(i=0;flag==1&&i<8;i++){
		digitalWrite(vector[i],HIGH);
                delay(*velocidad);
		if(i==0)digitalWrite(vector[7],LOW);
                if(i>0)digitalWrite(vector[i-1],LOW);
		flag=interrupt(op,velocidad,flag,modo,fd);
                delay(*velocidad);
                flag=interrupt(op,velocidad,flag,modo,fd);
        	}
	}
	for(i=1;i<9;i++)digitalWrite(vector[i],LOW);

}

void baliza(int *velocidad,char *vector,char modo,int fd,char op){
	int i,flag=1;
	grafica(op,velocidad);
	while(flag){
	flag=interrupt(op,velocidad,flag,modo,fd);
	for(i=0;flag==1&&i<8;i++)digitalWrite(vector[i],HIGH);
	delay(*velocidad);
	flag=interrupt(op,velocidad,flag,modo,fd);
	for(i=0;flag==1&&i<8;i++)digitalWrite(vector[i],LOW);
	delay(*velocidad);
	}
	for(i=0;i<8;i++)digitalWrite(vector[i],LOW);
}
void apilada(int *velocidad,char *vector,char modo,int fd,char op){
        int i,j,k=0;
	char flag=1;
        bool tarro[8][8]={
        {1,0,0,0,0,0,0,0},
        {0,1,0,0,0,0,0,0},
        {0,0,1,0,0,0,0,0},
        {0,0,0,1,0,0,0,0},
        {0,0,0,0,1,0,0,0},
        {0,0,0,0,0,1,0,0},
        {0,0,0,0,0,0,1,0},
        {0,0,0,0,0,0,0,1},
        };
	grafica(op,velocidad);
        while(flag){
            for(j=0;flag!=0&&j<8-k;j++){
                 for(i=0;flag!=0&&i<8-k;i++){
			flag=interrupt(op,velocidad,flag,modo,fd);
                        for(i=0;flag!=0&&i<8-k;i++){
				flag=interrupt(op,velocidad,flag,modo,fd);
                                digitalWrite(vector[i],tarro[i][j]);
                                delay(*velocidad);
                        }
                        if(j+k==7){
                                k++;digitalWrite(vector[8-k],0);
                                delay(*velocidad+100);
                                digitalWrite(vector[8-k],1);
			}
                        if(k==8){
				k=0;
				for(i=0;i<8;i++)
				digitalWrite(vector[i],0);
				delay(300);
			}
		}
                flag=interrupt(op,velocidad,flag,modo,fd);
        }
	}
        for(i=0;i<8;i++)digitalWrite(vector[i],0);
}
void vumetro_vertical(int *velocidad,char *vector,char modo,int fd,char op){
	int num=0,i;
	char flag=1;
	srand(time(NULL));
	grafica(op,velocidad);
        while(flag){
                num = rand()%9;
                num = rand()%9;
                for(i=0;i<num;i++){digitalWrite(vector[i],1);
                }delay(*velocidad);
                for(i=1;i<8;i++)digitalWrite(vector[i],0);
                flag=interrupt(op,velocidad,flag,modo,fd);

        }
        for(i=0;i<8;i++)digitalWrite(vector[i],0);
}
void vumetro_hor(int *velocidad,char *vector,char modo,int fd,char op){
        int num=0,i;
        char flag=1;
        srand(time(NULL));
	grafica(op,velocidad);
        while(flag){
                num = rand()%4;
                num = rand()%4;
                for(i=0;i<=num;i++){digitalWrite(vector[3-i],1);digitalWrite(vector[4+i],1);}
                delay(*velocidad);
                for(i=0;i<8;i++)digitalWrite(vector[i],0);
                flag=interrupt(op,velocidad,flag,modo,fd);
        }
        for(i=0;i<8;i++)digitalWrite(vector[i],0);

}
void seteo(int *velocidad,char modo,int fdd){
	int fd, result,flag=1;
	char op =12;
	printf("datos del sensor:\n");
	fd=wiringPiI2CSetup(0x48);
	while(flag){
	flag=interrupt(op,velocidad,flag,modo,fdd);
	wiringPiI2CWrite(fd,0);
        result=wiringPiI2CRead(fd);
	if(result)*velocidad=(result*250)/255;
	else *velocidad=result;
	delay(100);
	}
}
int maestro(int *velocidad,char modo){
	int fd;
	char op =9,dat,flag=1;
	grafica(op,velocidad);
	if ((fd = serialOpen ("/dev/ttyAMA0", 115200)) < 0)//APERTURA DEL PUERTO
 	{
 	printf ("No se pudo inicializar el puerto");
 	getchar();
	 return 1 ;
 	}
	while(flag){
	flag=interrupt(op,velocidad,flag,modo,fd);
	if(kbhit()){
		printf("%c %c",8,8);
                dat=getchar();
		switch(dat){
                        case '1':grafica(13,velocidad);break;
                        case '2':grafica(14,velocidad);break;
                        case '3':grafica(15,velocidad);break;
                        case '4':grafica(16,velocidad);break;
                        case '5':grafica(17,velocidad);break;
                        case '6':grafica(18,velocidad);break;
                        case '7':grafica(19,velocidad);break;
                        case '8':grafica(20,velocidad);break;
		}
		serialPutchar(fd, dat);
	}
	}
	serialClose(fd);
}
int esclavo(int *velocidad,char *vector){
	int fd;
        char op =10,dat,flag=1,modo=1;
	grafica(op,velocidad);
        if ((fd = serialOpen ("/dev/ttyAMA0", 115200)) < 0)//APERTURA DEL PUERTO
        {
        printf ("No se pudo inicializar el puerto");
        getchar();
         return 1 ;
        }
        while(flag){
        flag=interrupt(op,velocidad,flag,modo,fd);
        if(serialDataAvail(fd)){
                dat=serialGetchar(fd);
                switch(dat){
                        case '1':op=21;
				autofantastic(velocidad,vector,modo,fd,op);
				op=10;
				grafica(op,velocidad);break;
                        case '2':op=22;
				choque(velocidad,vector,modo,fd,op);
				op=10;
				grafica(op,velocidad);break;
                        case '3':op=23;
				apilada(velocidad,vector,modo,fd,op);
				op=10;
				grafica(op,velocidad);break;
                        case '4':op=24;
				carrera(velocidad,vector,modo,fd,op);
				op=10;
				grafica(op,velocidad);break;
                        case '5':op=25;
				anillo(velocidad,vector,modo,fd,op);
				op=10;
				grafica(10,velocidad);break;
                        case '6':op=26;
				vumetro_vertical(velocidad,vector,modo,fd,op);
				grafica(10,velocidad);break;
                        case '7':op=27;
				vumetro_hor(velocidad,vector,modo,fd,op);
				op=10;
				grafica(10,velocidad);break;
                        case '8':op=28;
				baliza(velocidad,vector,modo,fd,op);
				op=10;
				grafica(10,velocidad);break;
		}
        }
        }
        serialClose(fd);
}



void grafica(char op,int *velocidad){
	system("clear");//Al final va reset
        printf("%20c#####################################\n",35);
        printf("%20c Trabajo final Tecnicas Digitales 2 #\n",35);
        printf("%20c#####################################\n",35);
	printf("\n\n%10c Secuencias de luces:\n",62);
        if(op==1||op==13||op==21)printf("%13cx]",91);else printf("%13c ]",91);
	printf("(1) El auto fantastico.\n");
        if(op==2||op==14||op==22)printf("%13cx]",91);else printf("%13c ]",91);
	printf("(2) El choque.\n");
        if(op==3||op==15||op==23)printf("%13cx]",91);else printf("%13c ]",91);
	printf("(3) La apilada.\n");
        if(op==4||op==16||op==24)printf("%13cx]",91);else printf("%13c ]",91);
	printf("(4) La carrera.\n");
	if(op==5||op==17||op==25)printf("%13cx]",91);else printf("%13c ]",91);
	printf("(5) Anillo.\n");
	if(op==6||op==18||op==26)printf("%13cx]",91);else printf("%13c ]",91);
	printf("(6) Vumetro vertical.\n");
	if(op==7||op==19||op==27)printf("%13cx]",91);else printf("%13c ]",91);
	printf("(7) Vumetro horizontal.\n",91);
	if(op==8||op==20||op==28)printf("%13cx]",91);else printf("%13c ]",91);
	printf("(8) Baliza.\n");
	printf("\n %20celocidad: %d\n\n",86,((250-(*velocidad))*100)/250);
        printf("%10c Metodos de operacion:\n",62);
	if(op<9||op==12)printf("%13cx]",91);else printf("%13c ]",91);
	printf("( ) Local.\n");
	if(op==9||(op>12&&op<21))printf("%13cx]",91);else printf("%13c ]",91);
	printf("(m) Remoto-Maestro.\n");
	if(op==10||op>20)printf("%13cx]",91);else printf("%13c ]",91);
	printf("(e) Remoto-Esclavo.\n\n");
	printf("%10c Opciones\n",62);
        printf("%13cc) Salir de secuencias.\n",40);
        printf("%13cs) Setear velocidades iniciales.\n",40);
        printf("%13cx) Salir del programa.\n",40);
	if(op!=12)printf(": ");
}
