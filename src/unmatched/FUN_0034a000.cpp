extern "C" {
int Memory_GetAllocatorBySelector(int);
int igMetaObject_Create(int);
extern int DAT_00587040[4];
extern int DAT_00588298[4];
int FUN_0034a000(void);
}

int FUN_0034a000(void) {
    if (DAT_00588298[0] == 0) {
        DAT_00588298[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00588298[0];
}
