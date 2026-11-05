/* 0x0027d618 — FUN_0027d618. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_0027d4d0();
int memset();
int strncpy();

void FUN_0027d618(void *arg0, int arg1) {
    memset(*(int *)((char *)(arg0) + 0), 0, *(int *)((char *)(arg0) + 4));
    strncpy(*(int *)((char *)(arg0) + 0), arg1, 7);
    FUN_0027d4d0(*(int *)((char *)(arg0) + 4) - 0x10, *(int *)((char *)(arg0) + 0) + 8);
}
