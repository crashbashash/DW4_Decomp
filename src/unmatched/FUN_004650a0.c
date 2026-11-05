/* 0x004650a0 — FUN_004650a0. m2c draft + mechanical fixups, then verified
 * byte-identical to retail by tools/verify.py (see tools/m2c_batch.py).
 * The SHAPE matched; the C types are a guess. */
int FUN_00191f30();

void FUN_004650a0(void *arg0) {
    int sp1C;

    FUN_00191f30(&sp1C, (char *)arg0 + 0xC, *(int *)((char *)(arg0) + 8) + 0xC);
}
