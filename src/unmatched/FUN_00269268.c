/* 0x00269268 — FUN_00269268. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00267540();
int memset();
extern int DAT_004a5d70[4];
void FUN_00269268(void) {
    FUN_00267540();
    memset(&DAT_004a5d70[0], 0, 0x17C0);
}
