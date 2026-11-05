extern "C" {
int Memory_GetAllocatorBySelector(int);
int igMetaObject_Create(int);
extern int DAT_00587040[4];
extern int DAT_00589110[4];
int FUN_00359ff0(void);
}

int FUN_00359ff0(void) {
    if (DAT_00589110[0] == 0) {
        DAT_00589110[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00589110[0];
}
