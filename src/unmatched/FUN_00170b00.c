/* 0x00170b00 — FUN_00170b00. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
unsigned char FUN_00170b00(void *arg0, int arg1) {
    return *(int *)((char *)((*(int *)((char *)(*(int *)((char *)(arg0) + 1336)) + 16) + (arg1 * 0xA0))) + 148);
}
