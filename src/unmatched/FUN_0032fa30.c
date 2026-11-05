/* 0x0032fa30 — FUN_0032fa30. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int SleepThread();

void FUN_0032fa30(int *arg0) {
    SleepThread();
    *arg0 = *(int *)0x4FB410;
}
