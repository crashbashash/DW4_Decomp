extern "C" {
/* 0x00340490 - FUN_00340490. Near-miss sweep fix (alternate compiler), verified byte-identical to retail by tools/verify.py. */
int Memory_GetAllocatorBySelector(int);
int igMetaObject_Create(int);
extern int DAT_00587040[4];
extern int DAT_00587b88[4];
int FUN_00340490(void) {
    if (DAT_00587b88[0] == 0) {
        DAT_00587b88[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00587b88[0];
}
}
