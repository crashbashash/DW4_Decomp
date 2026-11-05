/* 0x001c1280 — FUN_001c1280. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_00562720[4];
void FUN_001c1280(void *arg0) {
    DAT_00562720[0] = *(int *)((char *)(arg0) + 160);
}
