#include <stdio.h>
#include <termios.h>
#include <string.h>
#include <stdlib.h>

#define PAS "5554555"
#define FD_STDIN 0
int main(){
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
	printf("\n Bienvenido. \n");
	break;
	}
	else printf("\n Contraseña incorrecta.\n");
	cont++;
	}while(cont<3);
}
