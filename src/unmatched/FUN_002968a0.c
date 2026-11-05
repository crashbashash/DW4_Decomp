/* 0x002968a0 — FUN_002968a0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002ad950();

void FUN_002968a0(void *arg0, int arg1) {
    FUN_002ad950(*(int *)((char *)(arg0) + 64), 0x2C, arg1);
}
