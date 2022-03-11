image: mos.disk
	@make -C ./boot
	@make -C ./kernel
	@dd if=boot/bootsector.bin of=mos.disk bs=512 count=1 conv=notrunc
	@dd if=boot/bootloader.bin of=mos.disk bs=512 count=16 seek=2 conv=notrunc
	@dd if=kernel/kernel.bin of=mos.disk bs=512 count=2048 seek=20 conv=notrunc
	@file mos.disk

debug: image
	bochs -q -f ./bochsrc
	
run: image
	@qemu-system-i386 mos.disk

mos.disk:
	@bximage -func=create -imgmode=flat -sectsize=512 -hd=60M -q mos.disk
	
.PHONY: clean
clean:
	rm -f mos.disk mos.disk.lock bochs.log mos.img
	make -C ./boot clean
	make -C ./kernel clean