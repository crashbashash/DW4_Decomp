extern "C" {
/* 0x0033fd70 - FUN_0033fd70. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
int Memory_GetAllocatorBySelector(int);
int igMetaObject_Create(int);
extern int DAT_00587040[4];
extern int DAT_00587a98[4];
int FUN_0033fd70(void) {
    if (DAT_00587a98[0] == 0) {
        DAT_00587a98[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00587a98[0];
}
}
