/* 0x00141900 — FUN_00141900. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
void FUN_00141900(void *arg0) {
    *(unsigned short *)((char *)(arg0) + 10) = (unsigned short) *(unsigned short *)((char *)(arg0) + 76);
}
