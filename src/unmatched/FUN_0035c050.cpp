/* 0x0035c050 - FUN_0035c050. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
extern "C" {
int Memory_GetAllocatorBySelector(int);
int igMetaObject_Create(int);
extern int DAT_00587040[4];
extern int DAT_00589258[4];
int FUN_0035c050(void);
}

int FUN_0035c050(void) {
    if (DAT_00589258[0] == 0) {
        DAT_00589258[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00589258[0];
}
