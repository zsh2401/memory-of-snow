ASSEMBLER=nasm -I ./inc
all: bootsector.bin bootloader.bin
	@ls -lh $^
	@file $^
bootsector.bin: bootsector.nasm ./inc/*.inc
	$(ASSEMBLER) bootsector.nasm -o bootsector.bin

bootloader.bin: bootloader.nasm ./inc/*.inc
	$(ASSEMBLER) bootloader.nasm -o bootloader.bin

.PHONY: clean
clean:
	rm -f bootsector.bin bootloader.bin