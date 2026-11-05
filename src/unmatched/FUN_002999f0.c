/* 0x002999f0 — FUN_002999f0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void *FUN_00299f68();

void FUN_002999f0(int arg0) {
    int (*temp_v0_2)(int);
    void *temp_v0;

    temp_v0 = (void *)(FUN_00299f68());
    if ((arg0 != 0) && (temp_v0 != 0)) {
        temp_v0_2 = (int (*)(int))(*(int *)((char *)(temp_v0) + 16));
        if (temp_v0_2 != 0) {
            temp_v0_2(arg0);
        }
    }
}
