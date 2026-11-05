/* 0x00294ef8 — FUN_00294ef8. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void *FUN_00294a30();

int FUN_00294ef8(int arg0) {
    *(int *)((char *)(FUN_00294a30()) + 104) = arg0;
    return arg0;
}
