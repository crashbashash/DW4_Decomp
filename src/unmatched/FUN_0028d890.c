/* 0x0028d890 — FUN_0028d890. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0028d8e0();
extern int DAT_004bcc68[4];
int FUN_0028d890(int arg0, int arg1) {
    if (arg0 == 0) {
        FUN_0028d8e0(DAT_004bcc68[0]);
    } else {
        FUN_0028d8e0(arg0 + 4);
    }
    return arg1;
}
