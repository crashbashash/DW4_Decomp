extern "C" {
int Memory_GetAllocatorBySelector(int);
int igMetaObject_Create(int);
extern int DAT_00587040[4];
extern int DAT_005891f0[4];
int FUN_0035b510(void);
}

int FUN_0035b510(void) {
    if (DAT_005891f0[0] == 0) {
        DAT_005891f0[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_005891f0[0];
}
