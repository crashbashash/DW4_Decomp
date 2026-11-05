/* 0x00245e80 — FUN_00245e80. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00246840();

void *FUN_00245e80(void *arg0, int arg1, int arg2, int arg3) {
    *(int *)((char *)arg0 + 0) = (int) (arg1 ^ arg2);
    *(int *)((char *)arg0 + 4) = 0;
    *(int *)((char *)arg0 + 8) = 0;
    FUN_00246840();
    *(int *)((char *)arg0 + 12) = arg2;
    *(int *)((char *)arg0 + 16) = arg3;
    *(int *)((char *)arg0 + 20) = arg1;
    return arg0;
}
