/* 0x00360780 - FUN_00360780. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
extern "C" {
int Memory_GetAllocatorBySelector(int);
int igMetaObject_Create(int);
extern int DAT_00587040[4];
extern int DAT_005895a0[4];
int FUN_00360780(void);
}

int FUN_00360780(void) {
    if (DAT_005895a0[0] == 0) {
        DAT_005895a0[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_005895a0[0];
}
