OBJECTS=start.o
CC=gcc -ffreestanding -m32 
LINEKR=ld
all: 	$(OBJECTS)
%.o : %.c
	$(CC) -c $< -o $@
.PHONY: clean
clean:
	rm -f *.o