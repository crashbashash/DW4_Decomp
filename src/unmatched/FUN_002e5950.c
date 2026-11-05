/* 0x002e5950 — FUN_002e5950. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_002e3cb0(void *);

void FUN_002e5950(int *arg0, void *arg1) {
    if (*(int *)((char *)arg1 + 196) != 0) {
        FUN_002e3cb0(arg1);
    }
    *arg0 = *(int *)0x4FB410;
}
