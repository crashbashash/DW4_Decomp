/* 0x00296248 — FUN_00296248. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00102df0();
int FUN_001033c0();

void FUN_00296248(void) {
    int temp_a0;
    int temp_s0;

    temp_s0 = FUN_00102df0();
    temp_a0 = temp_s0;
    do {

    } while (FUN_001033c0(temp_a0, 1, 0x1E) != 0);
}
