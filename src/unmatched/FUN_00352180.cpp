/* 0x00352180 - FUN_00352180. Near-miss sweep fix (alternate compiler), verified byte-identical to retail by tools/verify.py. */
extern "C" {
int Memory_GetAllocatorBySelector(int);
int igMetaObject_Create(int);
extern int DAT_00587040[4];
extern int DAT_00588ad0[4];
int FUN_00352180(void);
}

int FUN_00352180(void) {
    if (DAT_00588ad0[0] == 0) {
        DAT_00588ad0[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00588ad0[0];
}
