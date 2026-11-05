/* 0x001d8d50 — FUN_001d8d50. hand-matched: the real argument is the second/third (m2c
 * dropped the leading one); verified by tools/verify.py. */
int FUN_001d8d50(void *arg0, void *arg1) {
    return *(int *)((char *)(*(int *)((char *)(*(int *)((char *)(arg1) + 36)) + 8)) + 8) > 0;
}
