CC = gcc
CFILES= main.o kbhit.o
CLIB= wiringPi

main: $(CFILES)
	$(CC) $(CFILES) -l$(CLIB) -o main
clean:
	rm *.o main
