/* 0x0029cb30 — FUN_0029cb30. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern int DAT_004bead8[4];
int FUN_0029cb30(int arg0) {
    DAT_004bead8[0] = arg0;
    return 0;
}
