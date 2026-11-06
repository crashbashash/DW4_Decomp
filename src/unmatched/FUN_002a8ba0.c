void FUN_00113f20();
void FUN_00113f78();

/* EE DMAC registers. */
#define D_ENABLER ((volatile unsigned int *)0x1000F520)
#define D_ENABLEW ((volatile unsigned int *)0x1000F590)
#define D3_CHCR ((volatile unsigned int *)0x1000B000)   /* channel 3 (IPU_FROM) */

/* Writes the IPU_FROM DMA channel (3) CHCR with the DMAC suspended (D_ENABLEW bit 16), between
 * FUN_00113f20 and FUN_00113f78. */
void FUN_002a8ba0(unsigned int chcr) {
    FUN_00113f20();
    *D_ENABLEW = *D_ENABLER | 0x10000;
    *D3_CHCR = chcr;
    *D_ENABLEW = *D_ENABLER & ~0x10000;
    FUN_00113f78();
}
