/* 0x003c92c0 - FUN_003c92c0. Matches only with the alternate (combat) compiler build; see docs/engine/unit-compilers.md. */
/* The retail unit was C++ with exceptions on (it keeps an exception index record);
 * the code is C, so the whole unit keeps C linkage. */
extern "C" {
int Memory_GetAllocatorBySelector(int);
int igMetaObject_Create(int);
extern int DAT_00587040[4];
extern int DAT_0058bf90[4];
int FUN_003c92c0(void) {
    if (DAT_0058bf90[0] == 0) {
        DAT_0058bf90[0] = igMetaObject_Create(Memory_GetAllocatorBySelector(DAT_00587040[0]));
    }
    return DAT_0058bf90[0];
}
} /* extern "C" */
