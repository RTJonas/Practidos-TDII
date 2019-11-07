#include <stdio.h>
#include <string.h>
#include <wiringPi.h>
#include <wiringSerial.h>
int main ()
{
 int serial_port ;
 char dat;
 wiringPiSetup ();
 if ((serial_port = serialOpen ("/dev/ttyAMA0", 115200)) < 0)//APERTURA DEL PUERTO
 {
 printf ("No se pudo inicializar el puerto");
 getchar();
 return 1 ;
 }
 while(1){
 printf ("Ingrese carácter a enviar: ") ;
 scanf ("%c", &dat);
 serialPutchar(serial_port, dat);//ENVIO DE dat POR PIN Tx DE wiringPi
 }
}
