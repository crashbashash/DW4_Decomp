/* 0x0032ae70 — FUN_0032ae70. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0032f300();

void FUN_0032ae70(void) {
    if (*(int *)0x587218 == 0) {
        FUN_0032f300();
    }
}
