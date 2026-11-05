/* 0x002855d8 — FUN_002855d8. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00285628();
extern int DAT_004bcc50[4];
int FUN_002855d8(int arg0, int arg1) {
    if (arg0 == 0) {
        FUN_00285628(&DAT_004bcc50[0]);
    } else {
        FUN_00285628(arg0 + 4);
    }
    return arg1;
}
