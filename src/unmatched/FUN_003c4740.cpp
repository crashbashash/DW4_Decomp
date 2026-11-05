/* 0x003c4740 - FUN_003c4740. Near-miss sweep fix (alternate compiler), verified byte-identical to retail by tools/verify.py. */
extern "C" {
int Memory_GetAllocatorBySelector(int);
int igMetaObject_Create(int);
extern int DAT_00587040[4];
extern int DAT_0058bac8[4];
int FUN_003c4740(void);
}
int FUN_003c4740(void) {
    if (DAT_0058bac8[0] == 0) {
        DAT_0058bac8[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058bac8[0];
}
