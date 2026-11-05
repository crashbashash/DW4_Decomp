/* 0x0027ade8 — FUN_0027ade8. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_004b1dc0[4];
extern int DAT_004b1dc8[4];
void FUN_0027ade8(void *arg0, int arg1) {
    if ((DAT_004b1dc8[0] != 1) || (DAT_004b1dc0[0] > 0)) {
        *(int *)((char *)(arg0) + 48) = arg1;
    }
}
