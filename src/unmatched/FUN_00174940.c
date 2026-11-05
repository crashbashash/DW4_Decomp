/* 0x00174940 — FUN_00174940. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
unsigned char FUN_00174940(void *arg0) {
    return *(int *)((char *)(arg0) + 1228);
}
