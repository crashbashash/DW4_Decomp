/* 0x002ad910 — FUN_002ad910. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002a0bb8();
int FUN_002a0dd8();

int FUN_002ad910(void *arg0) {
    if (FUN_002a0dd8() != 0) {
        FUN_002a0bb8(0, 0xFF000111);
    }
    return *(int *)((char *)(arg0) + 72);
}
