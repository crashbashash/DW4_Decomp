/* 0x0032aca0 — FUN_0032aca0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_0032aca0(int arg0, unsigned int arg1, int arg2) {
    int *temp_a2;
    int temp_a3;

    temp_a3 = (arg1 & 0xF) * 2;
    temp_a2 = (int *)(arg0 + ((arg1 >> 4) * 4));
    *temp_a2 = (~(3 << temp_a3) & *temp_a2) | (arg2 << temp_a3);
}
