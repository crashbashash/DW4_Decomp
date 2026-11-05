extern "C" {
int Memory_GetAllocatorBySelector(int);
int igMetaObject_Create(int);
extern int DAT_00587040[4];
extern int DAT_00587ee8[4];
int FUN_003449b0(void) {
    if (DAT_00587ee8[0] == 0) {
        DAT_00587ee8[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00587ee8[0];
}
}
