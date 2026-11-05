/* 0x002b1790 — FUN_002b1790. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002b18d0();
extern int DAT_00585690[4];
extern int DAT_0058569c[4];
void FUN_002b1790(void) {
    int temp_v0;

    temp_v0 = DAT_0058569c[0] - 1;
    DAT_0058569c[0] = temp_v0;
    if (temp_v0 <= 0) {
        FUN_002b18d0(&DAT_00585690[0]);
    }
}
