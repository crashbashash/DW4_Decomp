/* 0x00174e90 — FUN_00174e90. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00174e90(void *arg0) {
    return *(int *)((char *)(arg0) + 1260) != 0;
}
