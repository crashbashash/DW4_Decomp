/* 0x0010d498 — FUN_0010d498. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern char DAT_00555fd8[];
int FUN_0010d498(int arg0, int arg1) {
    int temp_v0;

    temp_v0 = (int)*(int *)((char *)(DAT_00555fd8) + 20);
    *(int *)((char *)(DAT_00555fd8) + 24) = arg1;
    *(int *)((char *)(DAT_00555fd8) + 20) = arg0;
    return temp_v0;
}
