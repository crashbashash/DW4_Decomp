/* 0x00102620 — FUN_00102620. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_00546fb0[4];
extern int DAT_00554858[4];
int FUN_00102620(void *arg0) {
    *(int *)((char *)(arg0) + 12) = (int)(&DAT_00546fb0[0]);
    *(int *)((char *)(arg0) + 16) = (int)(&DAT_00554858[0]);
    return 1;
}
