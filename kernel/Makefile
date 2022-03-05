%.o : %.c
	gcc -ffreestanding -m64 -c $< -o $@
.PHONY: clean
clean:
	rm -f *.o