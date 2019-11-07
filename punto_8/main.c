#include <stdio.h>
#include <string.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <termios.h>
int main ()
{
int fd;
char dat;
 wiringPiSetup ();
 if ((fd = serialOpen ("/dev/ttyAMA0", 115200)) < 0)//APERTURA DEL PUERTO
 {
 printf ("No se pudo inicializar el puerto");
 getchar();
 return 1 ;
 }

 while(1){
 printf ("Ingrese carácter a enviar: ") ;
 dat=getchar();
 serialPutchar(fd, dat);
 }
}
