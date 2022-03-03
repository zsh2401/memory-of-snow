all: bootsector.bin bootloader.bin
	
bootsector.bin: bootsector.nasm ./inc/*.inc
	nasm bootsector.nasm -o bootsector.bin

bootloader.bin: bootloader.nasm ./inc/*.inc
	nasm bootloader.nasm -o bootloader.bin

.PHONY: clean
clean:
	rm -f bootsector.bin bootloader.bin