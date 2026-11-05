int igObject_Destroy(int *);
void FUN_002f8b20(void *arg0) {
    int *s2 = (int *)*(int *)((char *)arg0 + 20);
    int n = s2[2];
    int i;
    int m;
    int *p;
    int v;
    for (i = 0; i < n; i++) {
        p = ((int **)s2[4])[i];
        if (p != 0) {
            v = p[1] - 1;
            p[1] = v;
            if ((p[1] & 0x7FFFFF) == 0) {
                igObject_Destroy(p);
            }
        }
    }
    m = s2[2];
    for (i = 0; i < m; i++) {
        ((int *)s2[4])[i] = 0;
    }
    s2[2] = 0;
}
