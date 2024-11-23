TOOLPERFIX=i686-elf-
OBJECTS=$(shell cat objects.txt)
CC=$(TOOLPERFIX)gcc 
COMMON_CFLAGS=-ffreestanding -m32 -msse -D X86 
COMMON_CFLAGS+=-static-libgcc -lgcc -nostdlib
COMMON_CFLAGS+=-fno-stack-protector
COMMON_CFLAGS+=-Iinclude
CFLAGS=${COMMON_CFLAGS} -O2
ML_CFLAGS=${COMMON_CFLAGS} -O3 -ftree-vectorize -fopt-info
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

ml/%.o: ml/%.c
	$(CC) $(ML_CFLAGS) -c $< -o $@

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