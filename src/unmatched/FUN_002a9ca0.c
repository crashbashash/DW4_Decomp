/* 0x002a9ca0 — FUN_002a9ca0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002a96e0();
int FUN_002a9a30();

int FUN_002a9ca0(void *arg0, int arg1, int arg2) {
    if (FUN_002a96e0() == 0) {
        return arg2;
    }
    return FUN_002a9a30(*(int *)((char *)(arg0) + 8120) + 0x1118, arg1, arg2);
}
