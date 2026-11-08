typedef struct { int a; int b; int c; char p0[140]; int d; char p1[40]; int e; char p2[104]; int f; char p3[3948]; int g; } M;
typedef struct { int width; int height; int frameCount; char pad[52]; M *sys; } sceMpeg;
void FUN_00109a00(M *);
void FUN_00109910(M *);
int FUN_00109118(sceMpeg *mp) {
    M *m = mp->sys;
    m->g = 0;
    m->a = 0;
    m->b = 0;
    m->c = 0;
    mp->frameCount = 0;
    m->e = 0;
    m->d = -1;
    FUN_00109a00(m);
    m->f = 0;
    FUN_00109910(m);
    return 1;
}
