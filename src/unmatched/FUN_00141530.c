/* 0x00141530 — FUN_00141530. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0013b810(void *, short);
int FUN_0013b820();

void FUN_00141530(void *arg0) {
    FUN_0013b820();
    FUN_0013b810(arg0, *(int *)((char *)arg0 + 76));
}
