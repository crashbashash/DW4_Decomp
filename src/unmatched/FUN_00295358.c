/* 0x00295358 — FUN_00295358. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00294ef8(int);
int FUN_0029a320(int *);
int FUN_002aa4f0(int);
extern int DAT_004f3688[4];
int FUN_00295358(void *arg0) {
    int var_v0;

    var_v0 = FUN_002aa4f0(*(int *)((char *)arg0 + 64));
    if (var_v0 != 0) {
        FUN_00294ef8(-0x137);
        FUN_0029a320(&DAT_004f3688[0]);
        var_v0 = -0x137;
    }
    return var_v0;
}
