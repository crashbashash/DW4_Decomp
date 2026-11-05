extern "C" {
int Memory_GetAllocatorBySelector(int);
int igMetaObject_Create(int);
extern int DAT_00587040[4];
extern int DAT_005876e0[4];
int FUN_00335130(void) {
    if (DAT_005876e0[0] == 0) {
        DAT_005876e0[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_005876e0[0];
}
}
