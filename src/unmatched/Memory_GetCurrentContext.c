/* 0x002f8680 - Memory_GetCurrentContext. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
extern int DAT_00586fd0[4];
extern int DAT_00586ffc[4];
extern int DAT_00587010[4];
int Memory_GetCurrentContext(void) {
    if ((DAT_00587010[0] > 0) && (DAT_00587010[0] < 4)) {
        return DAT_00586ffc[DAT_00587010[0]];
    }
    if ((DAT_00587010[0] == 0) && (DAT_00586fd0[0] != 0)) {
        return DAT_00586fd0[0];
    }
    return 0;
}
