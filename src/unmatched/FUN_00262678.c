/* 0x00262678 - FUN_00262678. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
int FUN_002607e8();
extern int DAT_004edf20[4];
char FUN_00262678(void *arg0) {
    if (arg0 == 0) {
        FUN_002607e8(&DAT_004edf20[0]);
        return -3;
    }
    return *(int *)((char *)(arg0) + 1);
}
