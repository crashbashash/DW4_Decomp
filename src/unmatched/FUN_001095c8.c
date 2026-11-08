typedef struct { int a; int b; int c; char p0[184]; int e; char p1[104]; int n; int p2; int err; char p3[80]; int state; char p4[3856]; int g; } M;
typedef struct { int width; int height; int frameCount; char pad[52]; M *sys; } sceMpeg;
int FUN_001078f0(M *, int);
int FUN_00107790(M *);
void FUN_00107860(M *, int, int);
int FUN_00109280(sceMpeg *);
int FUN_001095c8(sceMpeg *mp, int a, int b) {
    M *m = mp->sys;
    int last = 0;
    int r;
    if (b == -1 || a < b) {
        if (m->c == 0) {
            mp->frameCount = 0;
            m->c = 1;
        }
        r = FUN_001078f0(m, 0);
        r = r && FUN_00107790(m);
    } else {
        r = FUN_001078f0(m, 0);
        last = 1;
        FUN_00109280(mp);
    }
    if (m->g != 0) return 0;
    FUN_00107860(m, m->n, m->b);
    if (m->state != 3 && !last) {
        m->err = !m->err;
    }
    mp->frameCount = m->n - m->e;
    if (m->err == 0) {
        m->n++;
        m->b++;
    }
    return r;
}
