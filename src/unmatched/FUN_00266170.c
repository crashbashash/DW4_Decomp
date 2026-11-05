/* 0x00266170 — FUN_00266170. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0025d4f8();
int FUN_0025f2d0();
int FUN_0025f2e8();
int memset();

void FUN_00266170(void *arg0) {
    int temp_v0;

    if (arg0 != 0) {
        temp_v0 = *(int *)((char *)(arg0) + 4);
        if (temp_v0 != 0) {
            *(int *)((char *)(arg0) + 4) = 0;
            FUN_0025d4f8(temp_v0);
        }
        FUN_0025f2d0();
        memset(arg0, 0, 0xA8);
        FUN_0025f2e8();
    }
}
