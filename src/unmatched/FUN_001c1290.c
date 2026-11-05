/* 0x001c1290 — FUN_001c1290. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002800d0();
extern int DAT_00562720[4];
void FUN_001c1290(void *arg0) {
    void *temp_a0;

    DAT_00562720[0] = 0;
    temp_a0 = (void *)(*(int *)((char *)(arg0) + 160));
    if ((temp_a0 != 0) && (*(unsigned char *)((char *)(temp_a0) + 171) != 0)) {
        FUN_002800d0(temp_a0);
    }
}
