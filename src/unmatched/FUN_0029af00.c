/* 0x0029af00 — FUN_0029af00. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void *FUN_00294a30();

int FUN_0029af00(void) {
    return *(int *)((char *)(FUN_00294a30()) + 88);
}
