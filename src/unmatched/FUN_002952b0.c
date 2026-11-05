/* 0x002952b0 — FUN_002952b0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void *FUN_00294a30();

int FUN_002952b0(void) {
    return *(int *)((char *)(FUN_00294a30()) + 52);
}
