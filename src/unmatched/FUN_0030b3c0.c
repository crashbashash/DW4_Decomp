/* 0x0030b3c0 — FUN_0030b3c0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int strlen(int);
int FUN_0030b320(int, int, int);
int FUN_0030b420();

void FUN_0030b3c0(int arg0, int arg1) {
    if (arg1 != 0) {
        FUN_0030b320(arg0, arg1, strlen(arg1));
        return;
    }
    FUN_0030b420();
}
