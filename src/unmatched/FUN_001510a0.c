/* 0x001510a0 — FUN_001510a0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMatrix44f_SetIdentity();

int FUN_001510a0(int arg0) {
    igMatrix44f_SetIdentity();
    return arg0;
}
