/* 0x00295fe8 — FUN_00295fe8. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00295fc8();
extern int (*DAT_004be894)(int, int);

void FUN_00295fe8(int arg0) {
    int temp_a1;

    temp_a1 = FUN_00295fc8();
    if (DAT_004be894 != 0) {
        DAT_004be894(arg0, temp_a1);
    }
}
