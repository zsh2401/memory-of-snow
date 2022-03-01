mos.disk:
	bximage -func=create -imgmode=flat -sectsize=512 -hd=50M -q mos.disk

.PHONY: clean
clean:
	make -C ./boot clean
	rm mos.disk