#ifndef EASYPIO_H
#define EASYPIO_H
#include <stdio.h>
#define INPUT (0)
#define OUTPUT (1)
#define HIGH (1)
#define LOW (0)

int pioInit();
void pinMode(int pin , int inout);
void digitalWrite(int pin , int status);
int digitalRead(int pin);
void delayMillis(int i);
#endif
