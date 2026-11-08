typedef struct { int a; int b; int c; char p0[184]; int d; char p1[104]; int e; } M;
typedef struct { int width; int height; int frameCount; char pad[52]; M *sys; } sceMpeg;
void FUN_00109920(M *);
int FUN_001098a8(sceMpeg *mp) {
    M *m = mp->sys;
    int r = 0;
    if (m->b != 0 && m->c != 0) {
        FUN_00109920(m);
        r = 1;
        mp->frameCount = m->e - m->d;
        m->b = 0;
    }
    return r;
}
