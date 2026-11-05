/* 0x00148ae0 — FUN_00148ae0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
extern char GPR_00554b18;

void FUN_00148ae0(void *arg0) {
    if (*(unsigned char *)((char *)(arg0) + 16) != 0) {
        GPR_00554b18 = 0;
    }
}
