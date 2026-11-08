typedef struct { char p0[200]; int a; char p1[36]; unsigned int b; int c; int d; int e; } M;
typedef struct { char pad[64]; M *sys; } sceMpeg;
int FUN_00109410(sceMpeg *);
int FUN_00109060(sceMpeg *mp, unsigned int addr, int w, int h) {
    M *m = mp->sys;
    addr = (addr & 0x0fffffff) | 0x20000000;
    m->b = addr;
    m->d = h << 4;
    m->e = w * h;
    m->c = w << 4;
    m->a = 0;
    return FUN_00109410(mp);
}
