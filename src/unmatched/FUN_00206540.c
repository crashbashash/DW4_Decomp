/* 0x00206540 — FUN_00206540. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_00206540(void) {
    *(long long *)0x56BEF0 = -1;
    *(long long *)0x56BEF8 = -1;
    *(long long *)0x56BF00 = -1;
    *(long long *)0x56BF08 = -1;
}
