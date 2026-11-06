/* Matches only with the alternate (combat) compiler build. */
extern "C" {
int Memory_GetAllocatorBySelector(int);
int igMetaObject_Create(int);
extern int DAT_00587040[4];
extern int DAT_005884c8[4];
int FUN_0034c080(void);
}

int FUN_0034c080(void) {
    if (DAT_005884c8[0] == 0) {
        DAT_005884c8[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_005884c8[0];
}
