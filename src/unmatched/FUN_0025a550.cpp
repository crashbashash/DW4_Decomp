extern "C" {
/* 0x0025a550 — FUN_0025a550. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00259f80(int);
int FUN_0025afe0();

void FUN_0025a550(int arg0) {
    FUN_0025afe0();
    FUN_00259f80(arg0);
}
}
