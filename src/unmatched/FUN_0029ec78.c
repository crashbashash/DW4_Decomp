/* 0x0029ec78 — FUN_0029ec78. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_0057fab4[4];
int FUN_0029ec78(void **arg0) {
    return ((int (*)())*(int *)((char *)((*arg0)) + 16))() == DAT_0057fab4[0];
}
