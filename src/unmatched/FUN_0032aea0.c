/* 0x0032aea0 — FUN_0032aea0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0032f330();

void FUN_0032aea0(void) {
    if (*(int *)0x587218 != 0) {
        FUN_0032f330();
    }
}
