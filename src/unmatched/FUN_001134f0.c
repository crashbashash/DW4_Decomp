/* Reports whether the IOP has flagged SIF as initialised: bit 0x10000 of SIF register 4 (sub-to-
 * main flag). */
unsigned int sceSifGetReg(unsigned int reg);

int FUN_001134f0(void) {
    if (sceSifGetReg(4) & 0x10000) {
        return 1;
    }
    return 0;
}
