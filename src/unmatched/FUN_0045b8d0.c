/* Matches only with the alternate (combat) compiler build. */
int Memory_GetAllocatorBySelector();
int igMetaObject_Create();
extern int DAT_00587040[4];
extern int DAT_0058cb28[4];
int FUN_0045b8d0(void) {
    if (DAT_0058cb28[0] == 0) {
        DAT_0058cb28[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058cb28[0];
}
