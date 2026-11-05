/* 0x002e2520 — FUN_002e2520. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002e2450();

void FUN_002e2520(int arg0, int arg1, void *arg2) {
    if ((arg2 != 0) && (arg1 < 0x10)) {
        *(int *)((char *)arg2 + 0) = FUN_002e2450();
        *(int *)((char *)arg2 + 4) = FUN_002e2450(arg0, arg1 + 1);
        *(int *)((char *)arg2 + 8) = FUN_002e2450(arg0, arg1 + 2);
    }
}
