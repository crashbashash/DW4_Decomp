/* 0x0012fce0 — FUN_0012fce0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int vfprintf();
extern void * DAT_004854a0[4];
void FUN_0012fce0(int arg0, int arg1) {
    vfprintf(*(int *)((char *)(DAT_004854a0[0]) + 8), arg0, arg1);
}
