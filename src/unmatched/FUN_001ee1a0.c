/* 0x001ee1a0 — FUN_001ee1a0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern void * DAT_00568e58[4];
void FUN_001ee1a0(void *arg0) {
    *(int *)((char *)arg0 + 20) = (int) DAT_00568e58[0];
    *(int *)((char *)arg0 + 24) = 0;
    DAT_00568e58[0] = arg0;
}
