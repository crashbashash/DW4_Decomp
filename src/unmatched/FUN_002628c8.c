/* 0x002628c8 — FUN_002628c8. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002607e8();
extern int DAT_004edf98[4];
void FUN_002628c8(void *arg0, int arg1) {
    if (*(char *)((char *)(arg0) + 1) == 2) {
        FUN_002607e8(&DAT_004edf98[0]);
        return;
    }
    *(int *)((char *)(arg0) + 44) = arg1;
}
