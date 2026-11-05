/* 0x00297838 — FUN_00297838. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002978b0();
int FUN_00297910();
int FUN_002979c8();
int FUN_002979e8();
int FUN_00297a30();

void FUN_00297838(int arg0, void *arg1, int *arg2) {
    *arg2 = FUN_002978b0(*(int *)((char *)(arg1) + 4));
    FUN_00297910(arg1, arg2);
    FUN_002979c8(arg1, arg2);
    FUN_002979e8(arg0, arg1, arg2);
    FUN_00297a30(arg0, arg2);
}
