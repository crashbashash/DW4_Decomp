/* 0x001ea8a0 — FUN_001ea8a0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern void * DAT_00562d88[4];
void FUN_001ea8a0(void *arg0) {
    *(int *)((char *)arg0 + 4) = (int) DAT_00562d88[0];
    *(int *)((char *)arg0 + 12) = 0;
    DAT_00562d88[0] = arg0;
    *(int *)((char *)arg0 + 8) = 0;
}
