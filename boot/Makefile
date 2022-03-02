bootsector.bin: bootsector.nasm ./inc/*.inc
	nasm bootsector.nasm -l bs.lst -o bootsector.bin

.PHONY: clean
clean:
	rm -f bootsector.bin bootsector.lst