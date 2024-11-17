TOOLPERFIX=i686-elf-
OBJECTS=$(shell cat objects.txt)
CC=$(TOOLPERFIX)gcc 
CFLAGS=-ffreestanding -m32 -D X86
CFLAGS+=-static-libgcc -lgcc -nostdlib
CFLAGS+=-fno-stack-protector
CFLAGS+=-Iinclude
LINEKR=$(TOOLPERFIX)ld
LDFLAGS=-m elf_i386 -T kernel.ld
ASSEMBLER=nasm
ASFLAG=-f elf
all: kernel.bin
	@ls -lh $^
	@file $^
kernel.bin: $(OBJECTS)
	$(LINEKR) $(LDFLAGS) $^  -o $@
%.ao: %.nasm
	$(ASSEMBLER) $(ASFLAG) -o $@ $^
	@file $@
%.o : %.c
	@echo "--- Object $@ Building---"
	$(CC) $(CFLAGS) -c $< -o $@
	@file $@
	@ls -lh $@
	@echo "--- Object $@ Built---"
.PHONY: clean
clean:
	-rm kernel.bin
	-rm $(OBJECTS)
	-make -C sche clean