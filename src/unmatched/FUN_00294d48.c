/* 0x00294d48 — FUN_00294d48. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void *FUN_00294a30();

void FUN_00294d48(int arg0) {
    *(int *)((char *)(FUN_00294a30()) + 60) = arg0;
}
