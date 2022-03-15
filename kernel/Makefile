OBJECTS=start.o tmgraph.o io.o
CC=gcc 
CFLAGS=-ffreestanding -m32 -fno-stack-protector
LINEKR=ld
LDFLAGS=-m elf_i386 -T kernel.ld 

all: kernel.bin
	@ls -lh $^
	@file $^
	
kernel.bin: $(OBJECTS)
	$(LINEKR) $(LDFLAGS) $^  -o $@

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@
.PHONY: clean
clean:
	rm -f *.o *.bin