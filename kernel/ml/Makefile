CFLAGS=-ffreestanding -m32 -D X86
CFLAGS+=-static-libgcc -lgcc
CFLAGS+=-fno-stack-protector
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@