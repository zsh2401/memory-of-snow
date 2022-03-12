# Memory
The minimal requirement of memory of MOS is 16MB
# Booting Stage
| P Addr |  Size -h | Usage | Remark| 
|--- | --- | --- | --- |
| 3C0000 - 7BFFFF | 4M | Page Table   | N/A |
| 2C0000 - 3BFFFF | 1M | kernel.bin   | buffer |
| 1C0000 - 2BFFFF | 1M | Kernel Stack | N/A  |
| C0000 - 1C0000 | 1M | Kernel | N/A |
| B8000 - BFFFF | 32KB | Video Memory | Text Mode |
| 8000 - 9FFF | 8KB | Bootloader | GDT is here | 
| 7E00 - 7FFF | 512 | Stack 0 | Booting Stack |
| 7C00 - 7DFF | 512 | MBR | N/A |
# Running Stage
TODO