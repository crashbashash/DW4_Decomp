/* 0x002b3d98 — FUN_002b3d98. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002b4b40();

void FUN_002b3d98(void *arg0) {
    FUN_002b4b40(*(int *)((char *)(arg0) + 40));
}
