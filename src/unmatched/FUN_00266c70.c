/* 0x00266c70 — FUN_00266c70. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0025ddc8();
int FUN_0025e4b8();
int FUN_002666b0();
int FUN_00266a18();
int FUN_00266be0();

void FUN_00266c70(void *arg0) {
    short temp_a0;
    void *temp_s0;

    temp_s0 = (void *)(*(int *)((char *)(arg0) + 4));
    if (FUN_0025ddc8(temp_s0) == 0) {
        FUN_002666b0(arg0);
    }
    FUN_0025e4b8(temp_s0);
    if (FUN_0025ddc8(temp_s0) == 3) {
        FUN_00266a18(arg0);
    }
    temp_a0 = *(int *)((char *)(temp_s0) + 152);
    if ((temp_a0 == 0xA) || (temp_a0 == 0x14) || (temp_a0 == 0xB) || (temp_a0 == 0xC) || (temp_a0 == 0xF)) {
        FUN_00266be0(arg0);
    }
}
