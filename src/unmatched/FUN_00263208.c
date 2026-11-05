/* 0x00263208 — FUN_00263208. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0026cbd8();
extern int DAT_0049c8f0[4];
void FUN_00263208(void) {
    DAT_0049c8f0[0] += 1;
    FUN_0026cbd8();
}
