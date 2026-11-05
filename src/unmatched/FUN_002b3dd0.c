/* 0x002b3dd0 — FUN_002b3dd0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002b30f0();

void FUN_002b3dd0(void *arg0) {
    FUN_002b30f0(*(int *)((char *)(arg0) + 52));
}
