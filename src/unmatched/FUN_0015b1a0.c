/* 0x0015b1a0 — 16 bytes. *(int *)(arg0 + 0xc) + arg2 * 2. arg2 is the THIRD
 * parameter (a2); the middle a1 argument is unused, so the two-parameter spelling
 * puts the value in a1 and misses by one register. */
int FUN_0015b1a0(int arg0, int arg1, int arg2) {
    return *(int *)((char *)(arg0) + 12) + (arg2 * 2);
}
