/* 0x00225770 — GpFlag_SetOnce_00225770. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern unsigned char DAT_00554bc8[4];
void GpFlag_SetOnce_00225770(void) {
    if (DAT_00554bc8[0] == 0) {
        DAT_00554bc8[0] = 1;
    }
}
