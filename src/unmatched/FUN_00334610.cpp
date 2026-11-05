extern "C" {
/* 0x00334610 - FUN_00334610. Matches only with the alternate (combat) compiler build; see docs/engine/unit-compilers.md. */
int Memory_GetAllocatorBySelector(int);
int igMetaObject_Create(int);
extern int DAT_00587040[4];
extern int DAT_00587630[4];
int FUN_00334610(void) {
    if (DAT_00587630[0] == 0) {
        DAT_00587630[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00587630[0];
}
}
