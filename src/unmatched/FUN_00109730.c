typedef struct { int a; int b; int c; char p0[184]; int e; char p1[36]; int f236; char p2[64]; int n; int p3; int err; char p4[80]; int state; char p5[3856]; int g; } M;
typedef struct { int width; int height; int frameCount; char pad[52]; M *sys; } sceMpeg;
int FUN_001078f0(M *, int);
int FUN_00107790(M *);
void FUN_00107860(M *, int, int);
int FUN_00106ee0(M *);
int FUN_001098a8(sceMpeg *);
int FUN_00109280(sceMpeg *);
int FUN_00109730(sceMpeg *mp, int a, int b) {
    M *m = mp->sys;
    int cont = 0;
    int r;
    int ok;
    int want;
    m->err = 0;
    if (b == -1 || a < b) cont = 1;
    if (m->c == 0) {
        mp->frameCount = 0;
        m->c = 1;
    }
    if (FUN_001078f0(m, 0) && cont) FUN_00107790(m);
    if (m->g != 0) return 0;
    m->err = 1;
    if (!FUN_00106ee0(m)) {
        FUN_001098a8(mp);
        m->a = 1;
        return 0;
    }
    want = 1;
    if (m->f236 == 1) want = 2;
    if (m->state != want) return -1;
    ok = 0;
    if (FUN_001078f0(m, 1)) ok = 1;
    r = 0;
    if (ok && cont && FUN_00107790(m)) r = 1;
    if (m->g != 0) return 0;
    FUN_00107860(m, m->n, m->b);
    m->err = 0;
    mp->frameCount = m->n - m->e;
    m->n++;
    m->b++;
    if (!cont) FUN_00109280(mp);
    return r;
}
