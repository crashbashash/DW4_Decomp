/* 0x001c1240 — FUN_001c1240. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001c16a0();
extern int DAT_00562718[4];
void FUN_001c1240(void *arg0) {
    int temp_a1;

    temp_a1 = *(int *)((char *)(arg0) + 160);
    if (temp_a1 != 0) {
        FUN_001c16a0(DAT_00562718[0], temp_a1, *(int *)((char *)(*(int *)((char *)(*(int *)((char *)(arg0) + 8)) + 20)) + 8));
    }
}
