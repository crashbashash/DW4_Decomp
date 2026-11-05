/* 0x002975e0 — FUN_002975e0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002ad950();

void FUN_002975e0(void *arg0, int arg1, int arg2) {
    FUN_002ad950(*(int *)((char *)(arg0) + 64), 0x5D, arg1);
    FUN_002ad950(*(int *)((char *)(arg0) + 64), 0x5E, arg2);
}
