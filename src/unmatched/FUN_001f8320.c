/* 0x001f8320 — FUN_001f8320. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int p2readGSPrivRegister(int);

void FUN_001f8320(void) {
    if (*(int *)0x490B60 != 0) {
        p2readGSPrivRegister(0x48);
    }
}
