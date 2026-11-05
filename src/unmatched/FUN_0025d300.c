/* 0x0025d300 — FUN_0025d300. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0025d078();
int FUN_0026ee48();
int memset();
extern int DAT_00498c80[4];
void FUN_0025d300(void) {
    FUN_0026ee48();
    FUN_0025d078();
    memset(&DAT_00498c80[0], 0, 0x1040);
}
