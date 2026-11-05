/* 0x00352410 - FUN_00352410. Matches only with the alternate (combat) compiler build; see docs/engine/unit-compilers.md. */
extern "C" {
int Memory_GetAllocatorBySelector(int);
int igMetaObject_Create(int);
extern int DAT_00587040[4];
extern int DAT_00588b00[4];
int FUN_00352410(void);
}

int FUN_00352410(void) {
    if (DAT_00588b00[0] == 0) {
        DAT_00588b00[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_00588b00[0];
}
