extern "C" {
int Memory_GetAllocatorBySelector(int);
int igMetaObject_Create(int);
extern int DAT_00587040[4];
extern int DAT_005894e8[4];
int FUN_0035f9d0(void);
}

int FUN_0035f9d0(void) {
    if (DAT_005894e8[0] == 0) {
        DAT_005894e8[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_005894e8[0];
}
