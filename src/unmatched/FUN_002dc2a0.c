/* 0x002dc2a0 — FUN_002dc2a0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002b9500();
int FUN_002c8450();
int Memory_GetAllocatorBySelector();
extern int DAT_005305f8[4];
extern int DAT_00530618[4];
extern int DAT_00587028[4];
extern int DAT_00587048[4];
extern int DAT_00587058[4];
extern unsigned char GPR_00554c14;

void *FUN_002dc2a0(void *arg0) {
    int var_v0;

    *(int *)((char *)(arg0) + 4) = (int)(&DAT_00530618[0]);
    *(int *)((char *)(arg0) + 0) = 1;
    *(int *)((char *)(arg0) + 4) = (int)(&DAT_005305f8[0]);
    if (GPR_00554c14 != 0) {
        var_v0 = Memory_GetAllocatorBySelector(DAT_00587028[0]);
    } else {
        var_v0 = Memory_GetAllocatorBySelector(DAT_00587058[0]);
    }
    *(int *)((char *)(arg0) + 8) = FUN_002c8450(var_v0);
    *(int *)((char *)(arg0) + 12) = FUN_002b9500(Memory_GetAllocatorBySelector(DAT_00587048[0]));
    return arg0;
}
