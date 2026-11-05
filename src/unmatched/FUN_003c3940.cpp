/* 0x003c3940 - FUN_003c3940. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
extern "C" {
int Memory_GetAllocatorBySelector(int);
int igMetaObject_Create(int);
extern int DAT_00587040[4];
extern int DAT_0058b958[4];
int FUN_003c3940(void);
}
int FUN_003c3940(void) {
    if (DAT_0058b958[0] == 0) {
        DAT_0058b958[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058b958[0];
}
