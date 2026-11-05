/* 0x00240440 — FUN_00240440. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_004986a0[4];
extern int DAT_004986a8[4];
extern int DAT_0056dea0[4];
extern int DAT_0056dea8[4];
extern int DAT_0056deb0[4];
void *FUN_00240440(void *arg0, unsigned int arg1) {
    int var_v0;

    *(int *)((char *)arg0 + 0) = (int) DAT_0056dea0[0];
    DAT_0056deb0[0] += 1;
    if (DAT_0056dea8[0] != 0) {
        var_v0 = *(int *)(DAT_0056dea8[0] + (((DAT_004986a8[0] - 1) & (arg1 ^ (arg1 >> DAT_004986a0[0]))) * 4));
    } else {
        var_v0 = 0;
    }
    *(int *)((char *)arg0 + 4) = var_v0;
    return arg0;
}
