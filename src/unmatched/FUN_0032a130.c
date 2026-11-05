/* 0x0032a130 — FUN_0032a130. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0032a220();

int FUN_0032a130(int arg0, long long arg1) {
    if (arg0 != 0) {
        if (((long long) (arg1 << 0x30) >> 0x30) > 0) {
            FUN_0032a220();
        }
    }
    return arg0;
}
