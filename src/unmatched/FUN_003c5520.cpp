extern "C" {
int Memory_GetAllocatorBySelector(int);
int igMetaObject_Create(int);
extern int DAT_00587040[4];
extern int DAT_0058bc10[4];
int FUN_003c5520(void);
}
int FUN_003c5520(void) {
    if (DAT_0058bc10[0] == 0) {
        DAT_0058bc10[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058bc10[0];
}
