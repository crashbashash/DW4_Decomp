/* 0x00350060 - FUN_00350060. Hand-reworked from the m2c draft; verified byte-identical to retail by tools/verify.py. */
extern "C" {
int Memory_GetAllocatorBySelector(int);
int igMetaObject_Create(int);
extern int DAT_00587040[4];
extern int DAT_00588888[4];
int FUN_00350060(void);
}

int FUN_00350060(void) {
    if (DAT_00588888[0] == 0) {
        DAT_00588888[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00588888[0];
}
