/* 0x00291438 — FUN_00291438. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002851d0();
int FUN_0028a958();
extern int DAT_00573f78[4];
void FUN_00291438(void) {
    FUN_0028a958();
    FUN_002851d0(8, &DAT_00573f78[0], 0x3840);
}
