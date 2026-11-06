int igMetaObject_Create(int);
int Memory_GetAllocatorBySelector(int);
extern int DAT_00561930[4];
extern int DAT_00587040[4];
int FUN_0019dfd0(void) {
    if (DAT_00561930[0] == 0) {
        DAT_00561930[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00561930[0];
}
