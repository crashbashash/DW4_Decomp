/* 0x2a0928 — FUN_002a0928. Verified byte-identical by tools/verify.py (wave3 sweep). */
int FUN_002a0928(void *arg0) {
    int r = 0;
    int t, m;
    arg0 = (char *)arg0 + 0x78;
    if (*(int *)arg0 != 0) {
        t = ((int *)arg0)[1];
        arg0 = (void *)((int *)arg0)[2];
        m = t * 3; m = m << 3; m = m + t; r = m << 2;
        r = r + (int)arg0;
    }
    return r;
}
