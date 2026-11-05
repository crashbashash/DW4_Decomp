/* 0x002e8a10 — FUN_002e8a10. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002e3cb0();

void FUN_002e8a10(void *arg0) {
    if (*(int *)((char *)arg0 + 196) > 0) {
        FUN_002e3cb0();
    }
}
