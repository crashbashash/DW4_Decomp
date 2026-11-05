/* 0x269630 — FUN_00269630, m2c draft + manual source-shape fix (finding #663),
 * verified byte-identical to retail by tools/verify.py. */
int FUN_00269630(void *arg0) {
    *(char *)((char *)(arg0) + 3) = 1;
    return 1;
}
