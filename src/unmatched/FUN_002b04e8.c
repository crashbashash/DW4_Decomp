/* 0x002b04e8 — FUN_002b04e8. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int memset();

void FUN_002b04e8(void *arg0) {
    memset((char *)arg0 + 0x18, 0, 0xF0);
    *(int *)((char *)(arg0) + 20) = 0;
    *(int *)((char *)(arg0) + 412) = (int)((int) (*(int *)((char *)(arg0) + 412) + 1));
}
