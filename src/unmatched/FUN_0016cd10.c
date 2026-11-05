/* 0x0016cd10 — FUN_0016cd10. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_001ee3f0();

void FUN_0016cd10(void *arg0) {
    if (*(int *)((char *)arg0 + 964) >= 0) {
        FUN_001ee3f0();
    }
}
