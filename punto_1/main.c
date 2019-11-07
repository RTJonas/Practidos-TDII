#include <stdio.h>
extern int switchcase(int a,int b, int c);
int main(){
int a,b,c;
printf("Opciones:\n 1) a+b. \n 2) a-b. \n 3) b-a. \n 4) a and b.\n ");
printf("Inserte opcion: ");
scanf("%d",&a);
printf("Operando a: ");
scanf("%d",&b);
printf("Operando b: ");
scanf("%d",&c);
a=switchcase(a,b,c);
printf("Resultado %d, %d,%d\n",a,b,c);
return 0;
}
