/* 0x0033c8e0 — GpFlag_SetOnce_0033c8e0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern unsigned char DAT_00554e50[4];
void GpFlag_SetOnce_0033c8e0(void) {
    if (DAT_00554e50[0] == 0) {
        DAT_00554e50[0] = 1;
    }
}
