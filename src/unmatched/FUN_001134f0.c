/* 0x001134f0 — FUN_001134f0 (40 bytes). Reports whether the IOP has flagged SIF as initialised: bit 0x10000 of SIF
 * register 4 (sub-to-main flag). ps2sdk reference: ee/kernel/include/sifdma.h (SIF_REG_SMFLAG = 4,
 * SIF_STAT_SIFINIT = 0x10000). Sony EE GCC 2.96 unit (docs/engine/sd-prologue.md). */
unsigned int sceSifGetReg(unsigned int reg);

int FUN_001134f0(void) {
    if (sceSifGetReg(4) & 0x10000) {
        return 1;
    }
    return 0;
}
