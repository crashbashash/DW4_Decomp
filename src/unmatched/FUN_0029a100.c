/* 0x0029a100 — FUN_0029a100. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0027e600();
extern int DAT_0057fa88[4];
void FUN_0029a100(int arg0, int arg1) {
    DAT_0057fa88[0] = FUN_0027e600(6, arg0, arg1);
}
