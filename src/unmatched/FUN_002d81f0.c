/* 0x002d81f0 — FUN_002d81f0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002d8230(void *, int);
int igProperty_FindByName(int, int, int);

void FUN_002d81f0(void *arg0, int arg1) {
    FUN_002d8230(arg0, igProperty_FindByName(*(int *)((char *)arg0 + 28), *(int *)0x585BE0, arg1));
}
