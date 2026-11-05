/* 0x00265838 — FUN_00265838. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_0056dfb8[4];
void FUN_00265838(void) {
    if (*(int *)((char *)&(DAT_0056dfb8[0]) + 0) != 0) {
        ((int (*)())*(int *)((char *)&(DAT_0056dfb8[0]) + 0))(*(int *)((char *)&(DAT_0056dfb8[0]) + 4));
    }
}
