/* 0x001f7340 — FUN_001f7340. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_001f7340(int arg0) {
    *(int *)0x569220 = arg0;
    *(int *)0x491478 = (int) (*(int *)0x491478 | 0x11);
}
