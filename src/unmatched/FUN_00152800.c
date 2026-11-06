int igMetaObject_Create(int);
int Memory_GetAllocatorBySelector(int);
extern int DAT_005604c0[4];
extern int DAT_00587040[4];
int FUN_00152800(void) {
    if (DAT_005604c0[0] == 0) {
        DAT_005604c0[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_005604c0[0];
}
