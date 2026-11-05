/* 0x00238d50 — GpFlag_SetOnce_00238d50. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern unsigned char DAT_00554bd4[4];
void GpFlag_SetOnce_00238d50(void) {
    if (DAT_00554bd4[0] == 0) {
        DAT_00554bd4[0] = 1;
    }
}
