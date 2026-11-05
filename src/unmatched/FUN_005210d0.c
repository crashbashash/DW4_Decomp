/* 0x005210d0 — FUN_005210d0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00100c20();
extern int DAT_0056da68[4];
extern int DAT_0056da78[4];
extern int DAT_0056da80[4];
extern int DAT_0056da90[4];
extern int DAT_0056da98[4];
extern int DAT_0056daa8[4];
int ObjectRef_Destruct_00150eb0();
int FUN_0022e3c0();

void FUN_005210d0(void) {
    DAT_0056da78[0] = 0;
    FUN_00100c20(&DAT_0056da78[0], &ObjectRef_Destruct_00150eb0, &DAT_0056da68[0]);
    DAT_0056da90[0] = 0;
    FUN_00100c20(&DAT_0056da90[0], &FUN_0022e3c0, &DAT_0056da80[0]);
    DAT_0056daa8[0] = 0;
    FUN_00100c20(&DAT_0056daa8[0], &ObjectRef_Destruct_00150eb0, &DAT_0056da98[0]);
}
