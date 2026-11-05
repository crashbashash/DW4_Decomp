extern "C" {
int Memory_GetAllocatorBySelector(int);
int igMetaObject_Create(int);
extern int DAT_00587040[4];
extern int DAT_005897d0[4];
int FUN_00363630(void);
}

int FUN_00363630(void) {
    if (DAT_005897d0[0] == 0) {
        DAT_005897d0[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_005897d0[0];
}
