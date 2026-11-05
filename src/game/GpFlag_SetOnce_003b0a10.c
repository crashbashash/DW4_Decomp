/* 0x003b0a10 — GpFlag_SetOnce_003b0a10. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern unsigned char DAT_00554e68[4];
void GpFlag_SetOnce_003b0a10(void) {
    if (DAT_00554e68[0] == 0) {
        DAT_00554e68[0] = 1;
    }
}
