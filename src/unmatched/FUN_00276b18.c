/* 0x00276b18 — FUN_00276b18. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern char DAT_004ab9f0[];
int FUN_00276a28();

void FUN_00276b18(int arg0, void *arg1) {
    int temp_v0;

    *(int *)((char *)(arg1) + 0) = 0;
    *(int *)((char *)(arg1) + 4) = 0;
    temp_v0 = *(int *)((char *)((int)DAT_004ab9f0) + 0);
    if (temp_v0 != 0) {
        FUN_00276a28(arg1, arg0, temp_v0, *(int *)((char *)((void *)DAT_004ab9f0) + 4));
    }
}
