/* 0x00366780 - FUN_00366780. Matches only with the alternate (combat) compiler build; see docs/engine/unit-compilers.md. */
extern "C" {
int Memory_GetAllocatorBySelector(int);
int igMetaObject_Create(int);
extern int DAT_00587040[4];
extern int DAT_005899c0[4];
int FUN_00366780(void);
}

int FUN_00366780(void) {
    if (DAT_005899c0[0] == 0) {
        DAT_005899c0[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_005899c0[0];
}
