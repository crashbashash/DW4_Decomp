/* 0x001033c0 — FUN_001033c0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00102c98();

int FUN_001033c0(unsigned int *arg0, int arg1) {
    if (arg1 == 1) {
        return ((unsigned int) *arg0 >> 8) & 1;
    }
    FUN_00102c98();
    return 0;
}
