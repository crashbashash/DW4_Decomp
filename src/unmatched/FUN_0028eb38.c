/* 0x0028eb38 — FUN_0028eb38. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0028eb88();
extern int DAT_004bccb8[4];
int FUN_0028eb38(int arg0, int arg1) {
    if (arg0 == 0) {
        FUN_0028eb88(&DAT_004bccb8[0]);
    } else {
        FUN_0028eb88(arg0 + 0x250);
    }
    return arg1;
}
