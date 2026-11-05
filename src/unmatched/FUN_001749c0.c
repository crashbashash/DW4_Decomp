/* 0x001749c0 — FUN_001749c0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_001749c0(void *arg0, unsigned char *arg1, unsigned char *arg2, unsigned char *arg3, unsigned char *arg4) {
    *arg1 = *(unsigned char *)((char *)(arg0) + 1252);
    *arg2 = *(unsigned char *)((char *)(arg0) + 1253);
    *arg3 = *(unsigned char *)((char *)(arg0) + 1254);
    *arg4 = *(unsigned char *)((char *)(arg0) + 1255);
}
