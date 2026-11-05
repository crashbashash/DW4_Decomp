/* 0x0023c440 — GpFlag_SetOnce_0023c440. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern unsigned char DAT_00554bdc[4];
void GpFlag_SetOnce_0023c440(void) {
    if (DAT_00554bdc[0] == 0) {
        DAT_00554bdc[0] = 1;
    }
}
