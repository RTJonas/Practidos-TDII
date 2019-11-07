#include <stdio.h>
extern void retardo(int a);
int main(){
int a=0;
printf("Inserte tiempo de retardo: \n");
scanf("%d",&a);
retardo(a);
printf("Listo.\n");
return 0;
}
