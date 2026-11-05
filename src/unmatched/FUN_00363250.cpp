extern "C" {
int Memory_GetAllocatorBySelector(int);
int igMetaObject_Create(int);
extern int DAT_00587040[4];
extern int DAT_00589790[4];
int FUN_00363250(void);
}

int FUN_00363250(void) {
    if (DAT_00589790[0] == 0) {
        DAT_00589790[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00589790[0];
}
