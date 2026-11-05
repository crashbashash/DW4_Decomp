extern "C" {
int Memory_GetAllocatorBySelector(int);
int igMetaObject_Create(int);
extern int DAT_00587040[4];
extern int DAT_005896d0[4];
int FUN_00362360(void);
}

int FUN_00362360(void) {
    if (DAT_005896d0[0] == 0) {
        DAT_005896d0[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_005896d0[0];
}
