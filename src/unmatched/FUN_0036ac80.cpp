/* 0x0036ac80 - FUN_0036ac80. Near-miss sweep fix (alternate compiler), verified byte-identical to retail by tools/verify.py. */
extern "C" {
int Memory_GetAllocatorBySelector(int);
int igMetaObject_Create(int);
extern int DAT_00587040[4];
extern int DAT_00589de8[4];
int FUN_0036ac80(void);
}

int FUN_0036ac80(void) {
    if (DAT_00589de8[0] == 0) {
        DAT_00589de8[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00589de8[0];
}
