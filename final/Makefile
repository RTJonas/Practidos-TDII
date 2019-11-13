CC = gcc
OBJECTS= main.o kbhit.o
CLIB= wiringPi

main: $(OBECTS)
	$(CC) -g $(OBJECTS) -o main
main.o: main.c
	$(CC) -c -g -l$(CLIB) main.c
kbhit.o: kbhit.c
	$(CC) -c -g kbhit.c 
clean:
	rm *.o main
