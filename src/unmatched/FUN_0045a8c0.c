/* 0x0045a8c0 - FUN_0045a8c0. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
int Memory_GetAllocatorBySelector();
int igMetaObject_Create();
extern int DAT_00587040[4];
extern int DAT_0058c928[4];
int FUN_0045a8c0(void) {
    if (DAT_0058c928[0] == 0) {
        DAT_0058c928[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058c928[0];
}
