/* 0x002661d8 — FUN_002661d8. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0025b968();
int FUN_0025bb50();

void FUN_002661d8(void *arg0, int arg1) {
    *(int *)((char *)(arg0) + 8) = arg1;
    FUN_0025bb50(*(int *)((char *)(arg0) + 4));
    FUN_0025b968(*(int *)((char *)(arg0) + 4), arg1);
}
