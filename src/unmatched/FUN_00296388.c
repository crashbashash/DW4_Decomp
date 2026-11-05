/* 0x00296388 — FUN_00296388. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002ad950();

void FUN_00296388(void *arg0, int arg1) {
    FUN_002ad950(*(int *)((char *)(arg0) + 64), 5, arg1);
}
