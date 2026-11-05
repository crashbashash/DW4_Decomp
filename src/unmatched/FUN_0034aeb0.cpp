/* 0x0034aeb0 - FUN_0034aeb0. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
extern "C" {
int Memory_GetAllocatorBySelector(int);
int igMetaObject_Create(int);
extern int DAT_00587040[4];
extern int DAT_005883b0[4];
int FUN_0034aeb0(void);
}

int FUN_0034aeb0(void) {
    if (DAT_005883b0[0] == 0) {
        DAT_005883b0[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_005883b0[0];
}
