typedef struct { int f0, f4, h, m, d, s, ms; short f28; short half; } Tm;
void FUN_002af2e8(int v, Tm *t, int *out, int *out2) {
    int m, days, secs, rest;
    m = t->m;
    secs = t->h * 107892 + m * 1798;
    rest = t->s + t->ms;
    days = (t->d * 15 + m / 10) * 2;
    *out = (days + secs + rest) * 1000 + t->half * 500;
    *out2 = v;
}
