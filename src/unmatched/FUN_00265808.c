/* 0x00265808 — FUN_00265808. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_0056dfb0[4];
void FUN_00265808(void) {
    if (*(int *)((char *)&(DAT_0056dfb0[0]) + 0) != 0) {
        ((int (*)())*(int *)((char *)&(DAT_0056dfb0[0]) + 0))(*(int *)((char *)&(DAT_0056dfb0[0]) + 4));
    }
}
