/* 0x00294d70 — FUN_00294d70. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void *FUN_00294a30();

int FUN_00294d70(void) {
    return *(int *)((char *)(FUN_00294a30()) + 60);
}
