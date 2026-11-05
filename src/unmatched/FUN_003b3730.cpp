/* 0x003b3730 - FUN_003b3730. Matches only with the alternate (combat) compiler build; see docs/engine/unit-compilers.md. */
extern "C" {
int Memory_GetAllocatorBySelector(int);
int igMetaObject_Create(int);
extern int DAT_00587040[4];
extern int DAT_0058ab58[4];
int FUN_003b3730(void);
}
int FUN_003b3730(void) {
    if (DAT_0058ab58[0] == 0) {
        DAT_0058ab58[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058ab58[0];
}
