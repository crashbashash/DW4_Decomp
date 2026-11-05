/* 0x00269298 — FUN_00269298. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00267560();
int memset();
extern int DAT_004a5d70[4];
void FUN_00269298(void) {
    FUN_00267560();
    memset(&DAT_004a5d70[0], 0, 0x17C0);
}
