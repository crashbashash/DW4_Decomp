/* 0x00149200 — FUN_00149200. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
unsigned short FUN_00149200(void *arg0) {
    return *(int *)((char *)(arg0) + 16);
}
