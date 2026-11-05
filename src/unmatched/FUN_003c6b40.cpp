extern "C" {
int Memory_GetAllocatorBySelector(int);
int igMetaObject_Create(int);
extern int DAT_00587040[4];
extern int DAT_0058bd98[4];
int FUN_003c6b40(void);
}
int FUN_003c6b40(void) {
    if (DAT_0058bd98[0] == 0) {
        DAT_0058bd98[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058bd98[0];
}
