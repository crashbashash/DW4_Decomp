/* 0x00105228 — FUN_00105228. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_00105228(int arg0) {
    *(int *)0x10002010 = (*(int *)0x10002010 & 0xFF7FFFFF) | (arg0 << 0x17);
}
