/* 0x2d3a50 — FUN_002d3a50. Verified byte-identical by tools/verify.py (wave3 sweep). */
int FUN_002d3a50(void *arg0) {
    void *obj;
    int *p;
    int n;
    int i;
    int cnt;

    obj = (void *)(*(int *)((char *)(arg0) + 16));
    cnt = 0;
    p = (int *)(*(int *)((char *)(obj) + 16));
    n = *(int *)((char *)(obj) + 8);
    for (i = 0; i < n; i++) {
        if (*p == 0) {
            cnt++;
        }
        p++;
    }
    return cnt;
}
