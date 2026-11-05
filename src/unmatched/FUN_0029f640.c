/* 0x0029f640 — FUN_0029f640. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0028b0c0();
int FUN_002a02d8();

void FUN_0029f640(int arg0, int arg1, void *arg2) {
    int temp_s0;

    temp_s0 = (arg1 < 0x801) ? arg1 : 0x800;
    FUN_0028b0c0((char *)arg2 + 0x94, arg0, temp_s0);
    *(int *)((char *)(arg2) + 144) = temp_s0;
    FUN_002a02d8(arg2);
}
