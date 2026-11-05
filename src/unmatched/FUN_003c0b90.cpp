extern "C" {
int Memory_GetAllocatorBySelector(int);
int igMetaObject_Create(int);
extern int DAT_00587040[4];
extern int DAT_0058b490[4];
int FUN_003c0b90(void);
}
int FUN_003c0b90(void) {
    if (DAT_0058b490[0] == 0) {
        DAT_0058b490[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058b490[0];
}
