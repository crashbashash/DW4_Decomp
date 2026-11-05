/* 0x002a8c08 — FUN_002a8c08 (100 bytes). Writes the IPU_TO DMA channel (4) CHCR with the DMAC suspended, inside the FUN_00113f20/FUN_00113f78 guard. Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
void FUN_00113f20();
void FUN_00113f78();

/* EE DMAC registers (addresses as in ps2sdk reference: common/include/ee_regs.h, ee/dma/include/dma_registers.h). */
#define D_ENABLER ((volatile unsigned int *)0x1000F520)
#define D_ENABLEW ((volatile unsigned int *)0x1000F590)
#define D4_CHCR ((volatile unsigned int *)0x1000B400)   /* channel 4 (IPU_TO) */

/* Writes the channel-4 CHCR with the DMAC suspended (D_ENABLEW bit 16), between FUN_00113f20 and FUN_00113f78. */
void FUN_002a8c08(unsigned int chcr) {
    FUN_00113f20();
    *D_ENABLEW = *D_ENABLER | 0x10000;
    *D4_CHCR = chcr;
    *D_ENABLEW = *D_ENABLER & ~0x10000;
    FUN_00113f78();
}
