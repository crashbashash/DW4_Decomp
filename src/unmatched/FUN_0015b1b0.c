/* 0x0015b1b0 — 16 bytes. As FUN_0015b1a0 but arg2 * 4 (retail `sll v1,a2,2`). */
int FUN_0015b1b0(int arg0, int arg1, int arg2) {
    return *(int *)((char *)(arg0) + 12) + (arg2 * 4);
}
