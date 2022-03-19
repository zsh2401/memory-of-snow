TOOLPERFIX=x86_64-elf-
OBJECTS=start.o tmgraph.o io.o mose.o util.o
CC=$(TOOLPERFIX)gcc 
CFLAGS=-ffreestanding -m32 -D X86
CFLAGS+=-static-libgcc -lgcc
CFLAGS+=-fno-stack-protector
LINEKR=$(TOOLPERFIX)ld
LDFLAGS=-m elf_i386 -T kernel.ld 
ASSEMBLER=nasm
ASFLAG=-f elf
all: kernel.bin
	@ls -lh $^
	@file $^
	
kernel.bin: $(OBJECTS)
	$(LINEKR) $(LDFLAGS) $^  -o $@
io.o: io.nasm
	$(ASSEMBLER) $(ASFLAG) -o $@ $^
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@
.PHONY: clean
clean:
	rm -f *.o *.bin *.s