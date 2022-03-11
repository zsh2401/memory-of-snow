# Memory
The minimal requirement of memory of MOS is 64MB
| P Addr |  Size -h | Usage | Remark| 
|--- | --- | --- | --- |
| 30000 - 43000 | 4M | Page Table   | N/A |
| 20000 - 2FFFF | 1M | kernel.bin   | buffer |
| 10000 - 1FFFF | 1M | Kernel Stack | N/A  |
| A000 - FFFFF | 1M | kernel | N/A |
| 8000 - A000 | 8192 | Bootloader | GDT is here | 
| 7e00 - 7FFF | 512 | Stack 0 | Booting Stack |
| 7c00 - 7DFF | 512 | MBR | N/A |