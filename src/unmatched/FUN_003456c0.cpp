extern "C" {
/* 0x003456c0 - FUN_003456c0. Matches only with the alternate (combat) compiler build; see docs/engine/unit-compilers.md. */
int Memory_GetAllocatorBySelector(int);
int igMetaObject_Create(int);
extern int DAT_00587040[4];
extern int DAT_00587f60[4];
int FUN_003456c0(void) {
    if (DAT_00587f60[0] == 0) {
        DAT_00587f60[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00587f60[0];
}
}
