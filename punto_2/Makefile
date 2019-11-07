CC= gcc
AS= as
LD= ld
ASM=retardo
CARCH=main
OBJECTS = $(CARCH).o $(ASM).o
CFLAGS = -Wall -O1 -g -c
ASFLAGS = -g
LDFLAGS = -g
out.elf: $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o out.elf
$(ASM).o: 
	$(AS) $(ASFLAGS) $(ASM).s -o $(ASM).o
main.o: $(CARCH).c
	$(CC) $(CFLAGS) $(CARCH).c
clean:
	rm *.o *.elf
