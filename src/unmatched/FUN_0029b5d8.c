/* 0x0029b5d8 — FUN_0029b5d8. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002632c0();
int FUN_00265f28();
int FUN_0028b530();
extern int DAT_0057fa90[4];
int FUN_0029b5d8(void) {
    FUN_002632c0();
    FUN_00265f28();
    FUN_0028b530(&DAT_0057fa90[0], 0, 7);
    return 0;
}
