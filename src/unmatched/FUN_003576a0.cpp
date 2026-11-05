extern "C" {
int Memory_GetAllocatorBySelector(int);
int igMetaObject_Create(int);
extern int DAT_00587040[4];
extern int DAT_00588f30[4];
int FUN_003576a0(void);
}

int FUN_003576a0(void) {
    if (DAT_00588f30[0] == 0) {
        DAT_00588f30[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00588f30[0];
}
