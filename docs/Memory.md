# Memory
The minimal requirement of memory of MOS is 64MB
| P Addr |  Size -h | Usage | Remark| 
|--- | --- | --- | --- |
| 30A000 - 709FFF | 4M | Page Table   | N/A |
| 20A000 - 309FFF | 1M | kernel.bin   | buffer |
| 10A000 - 209FFF | 1M | Kernel Stack | N/A  |
| A000 - FFFFF | 1M | Kernel | N/A |
| 8000 - A000 | 8192 | Bootloader | GDT is here | 
| 7e00 - 7FFF | 512 | Stack 0 | Booting Stack |
| 7c00 - 7DFF | 512 | MBR | N/A |