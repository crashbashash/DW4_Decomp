int Memory_GetAllocatorBySelector();
int igMetaObject_Create();
extern int DAT_00587040[4];
extern int DAT_0058ccf8[4];
int FUN_0045cf10(void) {
    if (DAT_0058ccf8[0] == 0) {
        DAT_0058ccf8[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058ccf8[0];
}
