/* 0x0044b860 — GpFlag_SetOnce_0044b860. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern unsigned char DAT_00554e74[4];
void GpFlag_SetOnce_0044b860(void) {
    if (DAT_00554e74[0] == 0) {
        DAT_00554e74[0] = 1;
    }
}
