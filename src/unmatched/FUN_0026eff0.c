/* 0x0026eff0 — FUN_0026eff0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_0026eff0(void *arg0, unsigned short *arg1, unsigned short *arg2, unsigned short *arg3) {
    *arg1 = *(unsigned short *)((char *)(arg0) + 52);
    *arg2 = *(unsigned short *)((char *)(arg0) + 54);
    *arg3 = *(unsigned short *)((char *)(arg0) + 56);
}
