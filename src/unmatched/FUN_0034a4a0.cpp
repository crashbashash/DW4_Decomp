extern "C" {
int Memory_GetAllocatorBySelector(int);
int igMetaObject_Create(int);
extern int DAT_00587040[4];
extern int DAT_00588330[4];
int FUN_0034a4a0(void);
}

int FUN_0034a4a0(void) {
    if (DAT_00588330[0] == 0) {
        DAT_00588330[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00588330[0];
}
