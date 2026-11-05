/* 0x00190c60 — FUN_00190c60. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int igMatrix44f_SetIdentity();

void FUN_00190c60(void *arg0, void *arg1) {
    igMatrix44f_SetIdentity();
    *(float *)((char *)(arg0) + 0) = (float) *(float *)((char *)(arg1) + 0);
    *(float *)((char *)(arg0) + 20) = (float) *(float *)((char *)(arg1) + 4);
    *(float *)((char *)(arg0) + 40) = (float) *(float *)((char *)(arg1) + 8);
}
