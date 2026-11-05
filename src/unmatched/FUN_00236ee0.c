/* 0x00236ee0 — FUN_00236ee0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002d6f50(int, int, int);
int FUN_00457ca0(int, int);

void FUN_00236ee0(void *arg0, int arg1) {
    FUN_00457ca0(arg1, *(int *)((char *)arg0 + 24));
    FUN_002d6f50(*(int *)((char *)arg0 + 28), arg1, 0);
}
